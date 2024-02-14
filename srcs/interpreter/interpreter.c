/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:47 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/14 16:56:11 by nlederge         ###   ########.fr       */
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

int	execute_job(t_tree *node, t_cmd_infos *infos, \
t_malloc_data *data)
{
	int	res;

	res = 1;
	if (!node)
		return (0);
	if (node->type == R_CMD_NAME)
		res = launch_cmd_sequence(node, infos, data);
	else if (node->type == R_IO_FILE_TO)
		res = add_io_file_to(node, infos);
	else if (node->type == R_IO_FILE_FROM)
		res = add_io_file_from(node, infos);
	else if (node->type == R_IO_FILE_DGREAT)
		res = add_io_file_append(node, infos);
	else if (node->type == R_IO_FILE_DLESS)
		res = add_io_file_here_doc(node, infos);
	if (res != 0 && !(data->ismain))
		return (free_data_infos(data, infos), exit_return(res), res);
	else if (res != 0)
		return (res);
	else
		return (execute_job(node->left, infos, data));
}

int	interpreter(t_malloc_data *data, t_tree **ast)
{
	int			res;
	t_cmd_infos	*infos;

	if (!ast)
		return (check_unknown_error(2), 1);
	data->ismain = 1;
	if ((*ast)->type != R_PIPE_SEQUENCE)
	{
		infos = ft_calloc(1, sizeof(t_cmd_infos));
		if (!infos)
			return (ft_perror(), 1);
		reset_cmd_infos(infos);
		res = execute_job(*ast, infos, data);
		res = return_status(infos, res);
	}
	else
		res = set_up_pipes(*ast, data, -1);
	return (res);
}
