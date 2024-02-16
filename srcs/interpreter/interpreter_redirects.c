/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:06:36 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 18:29:39 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	add_io_file_to(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_perror_str((node->right)->content), err(infos), 1);
	res = add_fd(infos, 'o', fd);
	return (res);
}

int	add_io_file_append(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_perror_str((node->right)->content), err(infos), 1);
	res = add_fd(infos, 'o', fd);
	return (res);
}

int	add_io_file_from(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDONLY);
	if (fd < 0)
		return (ft_perror_str((node->right)->content), err(infos), 1);
	res = add_fd(infos, 'i', fd);
	return (res);
}

int	add_io_file_here_doc(t_tree *node, t_cmd_infos *infos)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		return (ft_perror(), err(infos), 1);
	write(pipefd[1], node->content, ft_strlen(node->content));
	close(pipefd[1]);
	return (add_fd(infos, 'i', pipefd[0]));
}
