/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:26:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/25 17:55:02 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	**check_get_cmd(char **cmdin)
{
	char	**paths;
	char	*tmp;
	int		k;

	k = 0;
	paths = ft_split(getenv("PATH"), ':'); //careful env -I + use our envp or getenv
	if (!paths) //what to do in this case
		return (free_split(cmdin), NULL);
	while (paths[k])
	{
		tmp = ft_strjoin(paths[k], cmdin[0]);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (free(cmdin[0]), cmdin[0] = tmp, cmdin);
		free(tmp);
		k++;
	}
	free_split(NULL);
	return (NULL);
}

static int	cmd_split_count(t_tree *node)
{
	int		ct;
	t_tree	*it;

	ct = 1;
	it = node;
	while (it->right && (it->right)->type == R_CMD_SUFFIX)
	{
		ct++;
		it = it->right;
	}
	return (ct);
}

/*void	print_cmd(char **cmd)
{
	int	k;

	k = 0;
	if (!cmd)
		return ;
	ft_putendl_fd("checking cmd :", STDERR_FILENO);
	while (cmd[k])
		ft_putendl_fd(cmd[k++], STDERR_FILENO);
}*/

static char	**recreate_and_get_cmd(t_tree *node)
{
	int		ct;
	int		j;
	char	**cmd;
	t_tree	*it;

	ct = cmd_split_count(node);
	cmd = ft_calloc(ct + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	j = 0;
	it = node;
	while (j < ct)
	{
		if (j == 0)
			cmd[j] = ft_strjoin("/", it->content);
		else
			cmd[j] = ft_strdup(it->content);
		if (!cmd[j++])
			return(free_split(cmd), NULL);
		it = it->right;
	}
	cmd[j] = NULL;
	cmd = check_get_cmd(cmd);
	return (cmd);
}

int	launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, char *envp[])
{
	char	**cmd;

	if (!node)
		return (close_fds(infos, 0), -9); //define clean error codes
	cmd = recreate_and_get_cmd(node); //differentiate error and at which step
	if (!cmd)
		return (close_fds(infos, 0), -1); //exit properly child process
	manage_fds_for_cmd(infos);
	if (execve(cmd[0], cmd, envp) < 0)
		return (free_split(cmd), close_fds(infos, 0), 0); //exit properly in case of errors
	return (0);
}
