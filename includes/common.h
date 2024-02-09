/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:05 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:44:06 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "../libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/param.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

# define PROMPT "minishell: "
# define NOT_FOUND (t_tree *)-1
# define DQUOTE (char)-1000
# define SQUOTE (char)-1001
# define CMD_NOT_FOUND 127

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_tree
{
	char			*content;
	int				type;
	int				handle_expansion;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_ast_data
{
	int		count;
	int		start;
	t_token	**stream;
}	t_ast_data;

typedef struct s_cmd_infos
{
	int		pipe_readfd;
	int		use_pipe_read;
	int		pipe_writefd;
	int		use_pipe_write;
	int		*fds_in;
	int		fds_in_size;
	int		*fds_out;
	int		fds_out_size;
	pid_t	child_pid;
	int		status;
}	t_cmd_infos;

typedef enum e_token_type
{
	T_END=-1,
	T_WORD,
	T_PIPE,
	T_RET_FROM,
	T_RET_TO,
	T_DLESS,
	T_DGREAT
}	t_token_type;

typedef enum e_rules
{
	R_PIPE_SEQUENCE=1000,
	R_SIMPLE_CMD,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_IO_REDIRECT,
	R_IO_FILE_TO,
	R_IO_FILE_FROM,
	R_IO_FILE_DGREAT,
	R_IO_HERE,
	R_FILENAME,
	R_HERE_END
}	t_rules;

void	prompt(t_token *token, t_tree *ast, char **envp[]);

/*		ERRORS		*/

int		ft_perror(void);
int		print_error_lexer(int code, int *exit_status);
int		print_error_interpreter(int code);

/*		UTILS		*/

void	free_split(char **split);
int		return_status(t_cmd_infos *infos, int res);
char	**check_mandatory_envp(char *copied_envp[]);
char	**copy_envp(char *old_envp[]);
int		exit_return(int res);

/*		TOKENS AND LEXING		*/

int		lexer(char *line, t_token **token);
char	*lexer_expand_var_replace_quotes(char *line, char **envp);
char	*format_cmd_line(char *line, char **envp, int exit_status);

int		quote_sequence(int *table, char *line);
int		operator_sequence(int *table, char *line);

void	ft_tokendelone(t_token *lst);
void	ft_tokenclear(t_token **lst);
t_token	*ft_tokennew(void *content, int type);
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);
void	print_tokens(t_token **tokens);

/*		AST		*/

t_tree	*ast_builder(t_token **t);
t_tree	*create_node(int type, char *content, t_tree *left, t_tree *right);
void	consume_token(t_ast_data *d);

/*		AST - parse_functions	*/

t_tree	*parse_cmd_line(t_ast_data *d);
t_tree	*parse_simple_cmd(t_ast_data *d);
t_tree	*parse_io_redirect(t_ast_data *d);

/*			AST - utils		*/

int		is_token_type(t_token *t, int type);
int		is_io_file(t_token *t);
void	add_node_to_bottom_right(t_tree *main, t_tree *new_node);
void	add_node_to_bottom_left(t_tree *main, t_tree *new_node);
void	ft_treeclear(t_tree **lst);
void	free_ast_data(t_ast_data *d);
t_tree	*ft_treenew(void *content, int type);

int		check_dless(t_tree *tree);
void	print_ast(t_tree *tree, int indent_ct, char side);

/*		INTERPRETER		*/

int		interpreter(t_tree **ast, char **envp[]);
int		execute_job(t_tree *node, t_cmd_infos *infos, \
char **envp[], int ismain);

/*		INTERPRETER - PIPES		*/

int		set_up_pipes(t_tree *node, char **envp[], int pipefd_out, int ismain);

/*		INTERPRETER - ERRORS		*/

int		print_error_cmd(char *cmd, int status);
int		check_unknown_error(int status);

/*		INTERPRETER - UTILS		*/

char	**recreate_and_get_cmd(t_tree *node, char **envp, t_cmd_infos *infos);
int		cmd_split_count(t_tree *node);
void	reset_cmd_infos(t_cmd_infos *infos);
int		add_fd(t_cmd_infos *infos, char in_out, int fd);
void	close_fds(t_cmd_infos *infos, int notlast);
void	manage_fds_for_cmd(t_cmd_infos *infos);
int		launch_cmd_sequence(t_tree *node, \
t_cmd_infos *infos, char **envp[], int ismain);

/*		INTERPRETER - REDIRECTS		*/

int		add_io_file_to(t_tree *node, t_cmd_infos *infos);
int		add_io_file_from(t_tree *node, t_cmd_infos *infos);
int		add_io_file_append(t_tree *node, t_cmd_infos *infos);

/*		INTERPRETER - BUILTINS		*/

int		exec_builtin(int is_builtin, t_tree *node, \
char **envp[], t_cmd_infos *cmd_infos);
int		check_builtins(char *cmd);
int		check_env_var_format(char *content, char *cmd, int fd);
int		get_var_name_len(char *var);
int		get_double_arr_len(char **var);
int		builtin_export(char **cmd, char ***envp, int fd);
int		builtin_env(char **envp, int fd);
int		builtin_unset(char **cmd, char ***envp, int fd);
int		builtin_echo(char **cmd, int fd);
int		builtin_pwd(int fd);

/*		QUOTE FORMATING		*/

void	format_dquote_loop(char *old, int *flags, int *i, char **envp);
void	copy_env_var(char *old, char *new, int *i, char **envp);
int		get_env_len(char *old, int *flags, int *i, char **envp);
int		get_var_len(char *old, int *i);
int		get_env_index(char *var, int len, char **envp);
char	*format_quote(char *old, char **envp);
char	*copy_flagged(char *old, int *flags, char **envp, int exit_status);
int		get_flagged_len(char *old, int *flags);

#endif
