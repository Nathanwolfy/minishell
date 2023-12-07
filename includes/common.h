/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:05 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 11:42:41 by nlederge         ###   ########.fr       */
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

typedef struct s_stash
{
	char			**cmd;
	int				fdin_type;
	int				fdout_type;
	struct s_stash	*next;
}	t_stash;

typedef enum e_token_type
{
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HERE_DOC,
	T_REDIRECT_APP,
	T_WORD
}	t_token_type;

void	prompt(void);
void	lexer(char *line, int to, t_token **tree);
char	**ft_split_adapted(char *line, int to);

void	parser(t_stash **stash, t_token **tree);

int		ft_isspace(int c);
int		ft_is_sq(int c);
int		ft_is_dq(int c);
void	free_split(char **split);
void	print_tree(t_token **tree);
void	print_stash(t_stash **stash);

void	ft_tokendelone(t_token *lst, void (*del)(void*));
void	ft_tokenclear(t_token **lst, void (*del)(void*));
t_token	*ft_tokennew(void *content, int type);
t_token	*ft_tokenlast(t_token *lst);
void	ft_tokenadd_back(t_token **lst, t_token *new);

void	ft_stashdelone(t_stash *lst);
void	ft_stashclear(t_stash **lst);
t_stash	*ft_stashnew(char **content);
t_stash	*ft_stashlast(t_stash *lst);
void	ft_stashadd_back(t_stash **lst, t_stash *new);

#endif
