/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:06:36 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/23 17:31:29 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	add_io_file_to(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (-8); //define clean return codes
	res = add_fd(infos, 'o', fd);
	return (res);
}

int	add_io_file_from(t_tree *node, t_cmd_infos *infos)
{
	int	fd;
	int	res;

	fd = open((node->right)->content, O_RDONLY);
	if (fd < 0)
		return (-7); //define clean return codes
	res = add_fd(infos, 'i', fd);
	return (res);
}