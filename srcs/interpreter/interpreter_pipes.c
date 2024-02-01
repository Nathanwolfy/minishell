/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:05:59 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/01 16:54:56 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	close_all_pipefds(int pipefd[2], int pipefd_out)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (pipefd_out != -1)
		close(pipefd_out);
}

static int	set_up_pipe_left(t_tree *node, char **envp, int pipefd[2], int pipefd_out)
{
	t_cmd_infos	*infos;

	infos = ft_calloc(1, sizeof(t_cmd_infos));
	if (!infos)
		return (close_all_pipefds(pipefd, pipefd_out), -2); //define clear error codes exit here ?
	close(pipefd[0]);
	reset_cmd_infos(infos);
	add_fd(infos, 'o', pipefd[1]);
	if (pipefd_out != -1)
		close(pipefd_out);
	return (execute_job(node->left, infos, envp, 0));
}

static void	manage_fds_pipe_right(t_cmd_infos *infos, int pipefd[2], int pipefd_out)
{
	close(pipefd[1]);
	reset_cmd_infos(infos);
	add_fd(infos, 'i', pipefd[0]);
	if (pipefd_out != -1)
		add_fd(infos, 'o', pipefd_out);
}

int	set_up_pipes(t_tree *node, char *envp[], int pipefd_out, int ismain)
{
	int			pipefd[2];
	pid_t		pipe_pid;
	t_cmd_infos	*infos;

	if (pipe(pipefd) < 0)
		return (close_all_pipefds(NULL, pipefd_out), -3); //define clean error codes
	pipe_pid = fork();
	if (pipe_pid < 0)
		return (close_all_pipefds(pipefd, pipefd_out), -6); //define clean error codes
	else if (pipe_pid == 0)
	{
		if ((node->left)->type != R_PIPE_SEQUENCE)
			return (set_up_pipe_left(node, envp, pipefd, pipefd_out));
		else
			return (close(pipefd[0]), set_up_pipes(node->left, envp, pipefd[1], 0));
	}
	else
	{
		infos = ft_calloc(1, sizeof(t_cmd_infos));
		if (!infos)
			return (close_all_pipefds(pipefd, pipefd_out), -2); //define clear error codes exit here ?
		manage_fds_pipe_right(infos, pipefd, pipefd_out);
		//waitpid(pipe_pid, NULL, 0);
		return (execute_job(node->right, infos, envp, ismain));
	}
}
