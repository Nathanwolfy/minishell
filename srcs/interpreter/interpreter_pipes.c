/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:05:59 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 18:32:31 by nlederge         ###   ########.fr       */
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

static int	set_up_pipe_left(t_tree *node, t_malloc_data *data, \
int pipefd[2], int pipefd_out)
{
	t_cmd_infos	*infos;

	infos = ft_calloc(1, sizeof(t_cmd_infos));
	if (!infos)
		return (close_all_pipefds(pipefd, pipefd_out), ft_perror(), 1);
	close(pipefd[0]);
	reset_cmd_infos(infos);
	add_fd(infos, 'o', pipefd[1]);
	if (pipefd_out != -1)
		close(pipefd_out);
	return (data->ismain = 0, execute_job(node->left, infos, data));
}

static void	manage_fds_pipe_right(t_cmd_infos *infos, \
int pipefd[2], int pipefd_out)
{
	close(pipefd[1]);
	reset_cmd_infos(infos);
	add_fd(infos, 'i', pipefd[0]);
	if (pipefd_out != -1)
		add_fd(infos, 'o', pipefd_out);
}

static void	closeit(int pfd[2], t_malloc_data *data)
{
	close(pfd[0]);
	data->ismain = 0;
}

int	set_up_pipes(t_tree *node, t_malloc_data *data, int pipefd_out)
{
	int			pfd[2];
	pid_t		pipe_pid;
	t_cmd_infos	*infos;

	if (pipe(pfd) < 0)
		return (close_all_pipefds(NULL, pipefd_out), ft_perror(), 1);
	pipe_pid = fork();
	if (pipe_pid < 0)
		return (close_all_pipefds(pfd, pipefd_out), ft_perror(), 1);
	else if (pipe_pid == 0)
	{
		if ((node->left)->type != R_PIPE_SEQUENCE)
			return (set_up_pipe_left(node, data, pfd, pipefd_out));
		else
			return (closeit(pfd, data), set_up_pipes(node->left, data, pfd[1]));
	}
	else
	{
		infos = ft_calloc(1, sizeof(t_cmd_infos));
		if (!infos)
			return (close_all_pipefds(pfd, pipefd_out), ft_perror(), 1);
		manage_fds_pipe_right(infos, pfd, pipefd_out);
		return (return_status(infos, execute_job(node->right, infos, data)));
	}
}
