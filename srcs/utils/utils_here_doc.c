/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:17:13 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/12 15:15:54 by nlederge         ###   ########.fr       */
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

static char	*get_del(t_tree *node)
{
	return (node->right->content);
}

int	here_doc_sequence(t_tree *node)
{
	char	*line;
	char	*content;

	if (node->type == R_IO_FILE_DLESS)
	{
		content = ft_strdup("");
		if (!content)
			return (ft_perror(), 1);
		while (1)
		{
			write(STDOUT_FILENO, PROMPT_HERE_DOC, ft_strlen(PROMPT_HERE_DOC));
			line = get_next_line(STDIN_FILENO);
			if (!line)
				return (ft_perror(), 1);
			if (!ft_strncmp(line, get_del(node), ft_strlen(get_del(node))) \
			&& line[ft_strlen(get_del(node))] == '\n')
				break ;
			content = ft_strjoin_free(content, line, 3);
			if (!content)
				return (ft_perror(), 1);
		}
		free(node->content);
		node->content = content;
	}
	return (continue_browsing(node));
}
