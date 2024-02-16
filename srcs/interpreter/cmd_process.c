/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:26:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 12:57:51 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	child_sequence(t_tree *node, \
t_cmd_infos *infos, t_malloc_data *data)
{
	char	**cmd;

	if (!node)
		return (close_fds(infos, 0), ft_perror(), \
	free_data_infos(data, infos), 1);
	cmd = recreate_and_get_cmd(node, *(data->envp), infos);
	if (!cmd)
		return (close_fds(infos, 0), \
		exit_return(print_error_cmd(node->content, \
		infos->status, data, infos)));
	manage_fds_for_cmd(infos);
	if (execve(cmd[0], cmd, *(data->envp)) < 0)
		return (free_split(cmd), close_fds(infos, 0), \
	free_data_infos(data, infos), exit_return(1));
	return (exit_return(print_error_cmd(NULL, 2, data, infos)));
}

static int	handle_child_signal(int signum)
{
	if (signum == SIGQUIT)
		return (write(2, "Quit\n", 5), 131);
	else if (signum == SIGINT)
		return (130);
	return (0);
}

static int	check_child_signals(pid_t fork_pid, t_cmd_infos *infos)
{
	close_fds(infos, 0);
	waitpid(fork_pid, &infos->status, 0);
	wait(NULL);
	if (WIFSIGNALED(infos->status))
		return (handle_child_signal(WTERMSIG(infos->status)));
	return (0);
}

int	launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, \
t_malloc_data *data)
{
	pid_t	fork_pid;
	int		is_builtin;

	is_builtin = check_builtins(node->content);
	if (data->ismain && is_builtin < 0)
		fork_pid = fork();
	else
		fork_pid = 0;
	if (fork_pid < 0)
		return (close_fds(infos, 0), ft_perror(), 1);
	else if (is_builtin >= 0 && !data->ismain)
		return (exit_return(exec_builtin(is_builtin, node, data, infos)));
	else if (is_builtin >= 0)
		return (exec_builtin(is_builtin, node, data, infos));
	else if (fork_pid == 0)
	{
		return (child_sequence(node, infos, data));
	}
	return (check_child_signals(fork_pid, infos));
}
