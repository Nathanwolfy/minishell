/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:26:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:32:00 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	child_sequence(t_tree *node, t_cmd_infos *infos, char **envp[])
{
	char	**cmd;

	if (!node)
		return (close_fds(infos, 0), ft_perror(), 1);
	cmd = recreate_and_get_cmd(node, *envp, infos);
	if (!cmd)
		return (close_fds(infos, 0), \
		exit_return(print_error_cmd(node->content, infos->status)));
	manage_fds_for_cmd(infos);
	if (execve(cmd[0], cmd, *envp) < 0)
		return (free_split(cmd), close_fds(infos, 0), exit_return(1));
	return (exit_return(print_error_cmd(NULL, 2)));
}

int	launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, \
char **envp[], int ismain)
{
	pid_t	fork_pid;
	int		is_builtin;

	is_builtin = check_builtins(node->content);
	if (ismain && is_builtin < 0)
		fork_pid = fork();
	else
		fork_pid = 0;
	if (fork_pid < 0)
		return (close_fds(infos, 0), ft_perror(), 1);
	else if (is_builtin >= 0 && !ismain)
		return (exit_return(exec_builtin(is_builtin, node, envp, infos)));
	else if (is_builtin >= 0)
		return (exec_builtin(is_builtin, node, envp, infos));
	else if (fork_pid == 0)
	{
		return (child_sequence(node, infos, envp));
	}
	return (close_fds(infos, 0), \
	waitpid(fork_pid, &infos->status, 0), wait(NULL), 0);
}
