/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:17:13 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/19 15:53:51 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
How to do that :
- browse the ast to find the here_doc token just like we do in the interpreter
- once we find a here_doc token, read stdin and join all the lines until 
we find the delimiter
- assign the joined string to the here_doc token content
*/

static char	*ft_strjoin_free(char *s1, char *s2, int free_code)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (free_code == 1 || free_code == 3)
		free(s1);
	if (free_code == 2 || free_code == 3)
		free(s2);
	return (res);
}

static int	continue_browsing(t_tree *node)
{
	int	res;

	res = 0;
	if (node->left)
		res = here_doc_sequence(node->left);
	if (node->right && !res)
		res = here_doc_sequence(node->right);
	return (res);
}

static int	is_del(char **line, t_tree *node)
{
	if (!ft_strncmp(*line, node->right->content, \
	ft_strlen(node->right->content)) \
	&& (*line)[ft_strlen(node->right->content)] == '\n')
	{
		free(*line);
		return (1);
	}
	else
		return (0);
}

static int	here_doc_routine(t_tree *node, char **content)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = s_get_next_line(STDIN_FILENO);
		if (line == (char *)-1)
		{
			ft_putstr_fd("\nminishell: warning: here-document \
delimited by end-of-file (wanted `", STDOUT_FILENO);
			ft_putstr_fd(node->right->content, STDOUT_FILENO);
			ft_putendl_fd("\')", STDOUT_FILENO);
			break ;
		}
		else if (!line && g_sig == SIGINT)
			return (free(*content), 128 + SIGINT);
		else if (!line)
			return (free(*content), ft_perror(), 1);
		else if (is_del(&line, node))
			break ;
		*content = ft_strjoin_free(*content, line, 3);
		if (!*content)
			return (ft_perror(), 1);
	}
	return (0);
}

int	here_doc_sequence(t_tree *node)
{
	char	*content;
	int		res;

	if (node->type == R_IO_FILE_DLESS)
	{
		content = ft_strdup("");
		if (!content)
			return (ft_perror(), 1);
		res = here_doc_routine(node, &content);
		if (res != 0)
			return (res);
		free(node->content);
		node->content = content;
	}
	return (continue_browsing(node));
}
