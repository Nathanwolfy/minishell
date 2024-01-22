/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:26:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/22 17:58:24 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	cmd_split_count(t_tree *node)
{
	int		ct;
	t_tree	*it;

	ct = 1;
	it = node;
	while (it->right == R_CMD_SUFFIX)
	{
		ct++;
		it = it->right;
	}
	return (ct);
}

static char	**recreate_and_get_cmd(t_tree *node)
{
	int		ct;
	int		j;
	char	**cmd;
	t_tree	*it;

	ct = cmd_split_count(node);
	cmd = ft_calloc(ct, sizeof(char *));
	if (!cmd)
		return (NULL);
	j = 0;
	it = node;
	while (j < ct)
	{
		cmd[j] = ft_strdup(it->content);
		if (!cmd[j++])
			return(free_split(cmd), NULL);
		it = it->right;
	}
	cmd[j] = NULL;
	return (cmd);
}

int	launch_child_process(t_tree *node, t_cmd_infos *infos)
{
	char	**cmd;
	char	**envp; //how to get it ??

	if (!node)
		return (-9); //define clean error codes, , necessity to close all fds ?
	cmd = recreate_and_get_cmd(node); //add step to get PATH variable combined directly
	if (!cmd)
		return (-1); //exit properly child process, necessity to close all fds ?
	manage_fds_for_cmd(infos);
	if (execve(cmd[0], cmd, envp) < 0)
		return (free_split(cmd), 0); //exit properly in case of errors
	return (0);
}