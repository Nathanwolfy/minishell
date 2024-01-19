/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intrepreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:17:47 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/19 10:22:18 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	launch_cmd_sequence(t_tree *node, int pipefd[2], char wr)
{
	//check for redirs
	if (wr = 'w') //writing end
		launch();
	else if (wr = 'r') //reading end
		launch();
	else
		launch();
		
}

int	launch_pipe_sequence(t_tree *node)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0) //duplicate infos or fork directly here ?
		return (-3);
	launch_cmd_sequence(node->left, pipefd, 'w'); //not necessarily a PIPE
	launch_cmd_sequence(node->right, pipefd, 'r'); //catch return codes
	return (0);
}

int	execute_job(t_tree *node)
{
	int	res;

	res = -2;
	if (!node)
		return (-1);
	if (node->type == R_PIPE_SEQUENCE) //what if not a pipe
		res = launch_pipe_sequence(node);
	else if (node->type == R_CMD_NAME)
		
	return (res);		
}

int	interpreter(t_tree **ast)
{
	int		res;
	t_cmd_infos	infos;

	if (!ast)
		return (-1);
	reset_cmd_infos(&infos);
	res = execute_job(*ast);
	return (res);
}