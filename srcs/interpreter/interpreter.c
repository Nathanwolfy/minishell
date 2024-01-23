/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:47 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/23 18:42:12 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, char *envp[])
{
	pid_t	child_pid;

	//write(2, "launch_cmd_sequence\n", 21);
	child_pid = fork();
	if (child_pid < 0)
		return (-6); //define clean error codes
	else if (child_pid == 0)
		return (launch_child_process(node, infos, envp)); //how to handle pipes simply
	else
	{
		//write(2, "begin main process\n", 20);
		close_fds(infos, 0);
		infos->child_pid = child_pid;
		waitpid(infos->child_pid, NULL, 0);
		//write(2, "end main process\n", 18);
	}
	return (0);
}

int	launch_pipe_sequence(t_tree *node, t_cmd_infos *infos, char *envp[])
{
	int	pipefd[2];

	//write(2, "launch_pipe_sequence\n", 22);
	if (pipe(pipefd) < 0) //duplicate infos or fork directly here ?
		return (-3);
	launch_cmd_sequence(node->left, infos, envp); //not necessarily a PIPE
	launch_cmd_sequence(node->right, infos, envp); //catch return codes
	return (0);
}

int	execute_job(t_tree *node, t_cmd_infos *infos, char *envp[])
{
	int	res;

	res = -2;
	if (!node)
		return (-1);
	//write(2, "execute job\n", 13);
	if (node->type == R_PIPE_SEQUENCE) //what if not a pipe
		res = launch_pipe_sequence(node, infos, envp);
	else if (node->type == R_CMD_NAME)
		res = launch_cmd_sequence(node, infos, envp);
	else if (node->type == R_IO_FILE_TO)
		res = add_io_file_to(node, infos);
	else if (node->type == R_IO_FILE_FROM)
		res = add_io_file_from(node, infos);
	if (res < 0)
		return (res);
	else
		return (execute_job(node->left, infos, envp)); //what if pipe
}

int	interpreter(t_tree **ast, char *envp[])
{
	int			res;
	t_cmd_infos	*infos;

	infos = ft_calloc(1, sizeof(t_cmd_infos));
	if (!infos)
		return (-2); //define clear error codes
	if (!ast)
		return (-1);
	reset_cmd_infos(infos);
	res = execute_job(*ast, infos, envp);
	return (res);
}