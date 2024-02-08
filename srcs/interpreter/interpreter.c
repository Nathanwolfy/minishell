/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:47 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/08 20:00:58 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	print_error_interpreter(int code)
{
	if (code == -2)
		ft_putendl_fd("minishell: interpreter: missing ast", STDERR_FILENO);
	else if (code == -3)
		ft_putendl_fd("minishell: interpreter: missing shiet", STDERR_FILENO);
	return (code);
}

int	execute_job(t_tree *node, t_cmd_infos *infos, char **envp[], int ismain)
{
	int	res;

	res = -2;
	if (!node)
		return (0);
	if (node->type == R_CMD_NAME)
		res = launch_cmd_sequence(node, infos, envp, ismain);
	else if (node->type == R_IO_FILE_TO)
		res = add_io_file_to(node, infos);
	else if (node->type == R_IO_FILE_FROM)
		res = add_io_file_from(node, infos);
	else if (node->type == R_IO_FILE_DGREAT)
		res = add_io_file_append(node, infos);
	if (res < 0)
		return (res);
	else
		return (execute_job(node->left, infos, envp, ismain));
}

/*
0 : success
-1 : all types of errors handled by errno
-2 : missing ast
*/

int	interpreter(t_tree **ast, char **envp[])
{
	int			res;
	t_cmd_infos	*infos;

	if (!ast)
		return (-2);
	if ((*ast)->type != R_PIPE_SEQUENCE)
	{
		infos = ft_calloc(1, sizeof(t_cmd_infos));
		if (!infos)
			return (-1);
		reset_cmd_infos(infos);
		res = execute_job(*ast, infos, envp, 1);
		res = return_status(infos, res);
		free(infos);
	}
	else
		res = set_up_pipes(*ast, envp, -1, 1);
	return (res);
}
