/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:05 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 15:15:06 by nlederge         ###   ########.fr       */
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

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_tree
{
	char			*content;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef enum e_token_type
{
	T_END=-1,
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HERE_DOC,
	T_REDIRECT_APP
}	t_token_type;

typedef enum e_sequence_type
{
	S_CMD=1000,
	S_PIPE,
	S_REDIR
}	t_sequence_type;

void	prompt(void);
void	lexer(char *line, int to, t_token **token);
char	**ft_split_adapted(char *line, int to);

//void	parser(t_token **token, t_tree **ast);

void	interpreter(t_tree **ast, t_tree *node);

int		ft_isspace(int c);
int		ft_is_sq(int c);
int		ft_is_dq(int c);
void	free_split(char **split);
void	print_token(t_token **token);

void	ft_tokendelone(t_token *lst);
void	ft_tokenclear(t_token **lst);
t_token	*ft_tokennew(void *content, int type);
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);

#endif
