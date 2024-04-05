/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:26:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/20 17:17:29 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	child_sequence(t_tree *node, \
t_cmd_infos *infos, t_malloc_data *data)
{
	char	**cmd;
	int		res;

	if (!node)
		return (ft_perror(), close_fds(infos, 0), \
	free_data_infos(data, infos), 1);
	cmd = recreate_and_get_cmd(node, *(data->envp), infos);
	if (!cmd)
	{
		res = print_error_cmd(node->content, \
		infos->status, data, infos);
		close_fds(infos, 0);
		return (exit_return(res));
	}
	manage_fds_for_cmd(infos);
	if (execve(cmd[0], cmd, *(data->envp)) < 0)
		return (free_split(cmd), close_fds(infos, 0), \
	free_data_infos(data, infos), exit_return(1));
	return (free_split(cmd), close_fds(infos, 0), \
	print_error_cmd(NULL, 2, data, infos), free_data_infos(data, infos), \
	exit(2), 2);
}

int	launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, \
t_malloc_data *data)
{
	pid_t	fork_pid;
	int		res;

	infos->is_builtin = check_builtins(node->content);
	if (data->ismain && infos->is_builtin < 0)
		fork_pid = fork();
	else
		fork_pid = 0;
	if (fork_pid < 0)
		return (ft_perror(), close_fds(infos, 0), 1);
	else if (infos->is_builtin >= 0 && !data->ismain)
		return (res = exec_builtin(infos->is_builtin, \
		node, data, infos), free_data_infos(data, infos), \
		exit_return(res));
	else if (infos->is_builtin >= 0)
		return (exec_builtin(infos->is_builtin, node, data, infos));
	else if (fork_pid == 0)
	{
		return (child_sequence(node, infos, data));
	}
	return (close_fds(infos, 0), s_ign(), waitpid(fork_pid, &(infos->status) \
	, 0), waitpid(fork_pid, &(infos->status), 0), infos->status);
}
