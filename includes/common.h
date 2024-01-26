/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:05 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/26 14:39:03 by nlederge         ###   ########.fr       */
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
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# define PROMPT "minishell: "
# define NOT_FOUND (t_tree *)-1

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
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct	s_ast_data
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

void	prompt(char *envp[]);

/*		UTILS		*/

int		ft_isspace(int c);
int		ft_is_sq(int c);
int		ft_is_dq(int c);
void	free_split(char **split);
char	**copy_envp(char *old_envp[]);

/*		TOKENS AND LEXING		*/

int		lexer(char *line, t_token **token);
int		lexer_rec(char *line, int to, t_token **token);
char	**ft_split_adapted(char *line, int to);

int		unclosed_quotes_code(int sq, int dq);
int		print_error_lexing_code(int code);

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

int		interpreter(t_tree **ast, char *envp[]);
int		execute_job(t_tree *node, t_cmd_infos *infos, char *envp[]);

/*		INTERPRETER - PIPES		*/

int		set_up_pipes(t_tree *node, char *envp[], int pipefd_out);

/*		INTERPRETER - UTILS		*/

void	reset_cmd_infos(t_cmd_infos *infos);
int		add_fd(t_cmd_infos *infos, char in_out, int fd);
void	close_fds(t_cmd_infos *infos, int notlast);
void	manage_fds_for_cmd(t_cmd_infos *infos);
int		launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, char *envp[]);

/*		INTERPRETER - REDIRECTS		*/

int		add_io_file_to(t_tree *node, t_cmd_infos *infos);
int		add_io_file_from(t_tree *node, t_cmd_infos *infos);
int		add_io_file_append(t_tree *node, t_cmd_infos *infos);

#endif
