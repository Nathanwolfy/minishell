/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:47 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/25 18:08:30 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	execute_job(t_tree *node, t_cmd_infos *infos, char *envp[])
{
	int	res;

	res = -2;
	if (!node)
		return (-1);
	if (node->type == R_CMD_NAME)
		res = launch_cmd_sequence(node, infos, envp);
	else if (node->type == R_IO_FILE_TO)
		res = add_io_file_to(node, infos);
	else if (node->type == R_IO_FILE_FROM)
		res = add_io_file_from(node, infos);
	else if (node->type == R_IO_FILE_DGREAT)
		res = add_io_file_append(node, infos);
	if (res < 0)
		return (res);
	else
		return (execute_job(node->left, infos, envp));
}

static int	set_up_pipes(t_tree *node, char *envp[], int pipefd_in, int pipefd_out)
{
	int			pipefd[2];
	pid_t		pipe_pid;
	t_cmd_infos	*infos;

	if (pipe(pipefd) < 0)
		return (-3);
	if ((node->left)->type != R_PIPE_SEQUENCE)
	{
		pipe_pid = fork();
		if (pipe_pid < 0)
			return (-6); //define clean error codes
		else if (pipe_pid == 0)
		{
			close(pipefd[0]);
			infos = ft_calloc(1, sizeof(t_cmd_infos));
			if (!infos)
				return (close(pipefd[1]), -2); //define clear error codes exit here ?
			reset_cmd_infos(infos);
			add_fd(infos, 'o', pipefd[1]);
			if (pipefd_out != -1)
				close(pipefd_out);
			if (pipefd_in != -1)
				add_fd(infos, 'i', pipefd_in);
			return (execute_job(node->left, infos, envp));
		}
		else
		{
			close(pipefd[1]);
			infos = ft_calloc(1, sizeof(t_cmd_infos));
			if (!infos)
				return (close(pipefd[0]), -2); //define clear error codes exit here ?
			reset_cmd_infos(infos);
			add_fd(infos, 'i', pipefd[0]);
			if (pipefd_out != -1)
				add_fd(infos, 'o', pipefd_out);
			if (pipefd_in != -1)
				close(pipefd_in);
			waitpid(pipe_pid, NULL, 0);
			return (execute_job(node->right, infos, envp));
		}
	}
	else
	{
		pipe_pid = fork();
		if (pipe_pid < 0)
			return (-6); //define clean error codes
		else if (pipe_pid == 0)
		{
			close(pipefd[0]);
			set_up_pipes(node->left, envp, -1, pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			infos = ft_calloc(1, sizeof(t_cmd_infos));
			if (!infos)
				return (close(pipefd[0]), -2); //define clear error codes exit here ?
			reset_cmd_infos(infos);
			add_fd(infos, 'i', pipefd[0]);
			if (pipefd_out != -1)
				add_fd(infos, 'o', pipefd_out);
			if (pipefd_in != -1)
				close(pipefd_in);
			waitpid(pipe_pid, NULL, 0);
			return (execute_job(node->right, infos, envp));
		}
		return (0);
	}
}

int	interpreter(t_tree **ast, char *envp[])
{
	int			res;
	t_cmd_infos	*infos;
	pid_t 		child_pid;

	if (!ast)
		return (-1);
	child_pid = fork();
	if (child_pid < 0)
		return (-6); //define clean error codes
	else if (child_pid == 0)
	{
		if ((*ast)->type != R_PIPE_SEQUENCE)
		{
			infos = ft_calloc(1, sizeof(t_cmd_infos));
			if (!infos)
				return (-2); //define clear error codes
			reset_cmd_infos(infos);
			res = execute_job(*ast, infos, envp);
		}
		else
			res = set_up_pipes(*ast, envp, -1, -1);
		res = res + 1;
		exit(0);
	}
	else
		waitpid(child_pid, NULL, 0);
	return (0);
}
