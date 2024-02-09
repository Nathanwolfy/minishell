/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:06:36 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/08 20:15:24 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
0 : success
-1 : malloc error, not yet displayed
-2 : fd error, already displayed
*/

int	add_io_file_to(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror((node->right)->content), -2);
	res = add_fd(infos, 'o', fd);
	return (res);
}

int	add_io_file_append(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror((node->right)->content), -2);
	res = add_fd(infos, 'o', fd);
	return (res);
}

int	add_io_file_from(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDONLY);
	if (fd < 0)
		return (perror((node->right)->content), -2);
	res = add_fd(infos, 'i', fd);
	return (res);
}