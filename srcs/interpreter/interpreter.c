/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:47 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/31 14:49:15 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	execute_job(t_tree *node, t_cmd_infos *infos, char *envp[], int isfirst)
{
	int	res;

	res = -2;
	if (!node)
		return (-1);
	if (node->type == R_CMD_NAME)
		res = launch_cmd_sequence(node, infos, envp, isfirst);
	else if (node->type == R_IO_FILE_TO)
		res = add_io_file_to(node, infos);
	else if (node->type == R_IO_FILE_FROM)
		res = add_io_file_from(node, infos);
	else if (node->type == R_IO_FILE_DGREAT)
		res = add_io_file_append(node, infos);
	if (res < 0)
		return (res);
	else
		return (execute_job(node->left, infos, envp, isfirst));
}

int	interpreter(t_tree **ast, char *envp[])
{
	int			res;
	t_cmd_infos	*infos;
	pid_t 		child_pid;

	if (!ast)
		return (-1);
	if ((*ast)->type != R_PIPE_SEQUENCE)
	{
		infos = ft_calloc(1, sizeof(t_cmd_infos));
		if (!infos)
			return (-2); //define clear error codes
		reset_cmd_infos(infos);
		res = execute_job(*ast, infos, envp, 1);
	}
	else
		res = set_up_pipes(*ast, envp, -1, 1);
	return (res);
}
