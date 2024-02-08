/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:11 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/08 20:00:11 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	create_builtins(char *builtins[7])
{
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
}

int	check_builtins(char *cmd)
{
	char	*builtins[7];
	int		i;

	create_builtins(builtins);
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen(builtins[i]))
			return (i);
		i++;
	}
	return (-1); //define error code
}

static int manage_fds_for_builtins(t_cmd_infos *infos)
{
	int	k;
	int	fd;

	fd = STDOUT_FILENO;
	if (!infos)
		return (fd);
	k = 0;
	while (k < infos->fds_in_size)
		close((infos->fds_in)[k++]);
	k = 0;
	while (k < infos->fds_out_size - 1)
		close((infos->fds_out)[k++]);
	if (infos->fds_out_size > 0)
		fd = (infos->fds_out)[k];
	return (fd);
}

static void close_fd_builtin(int fd)
{
	if (fd != STDOUT_FILENO && fd > 0)
		close(fd);
}

int	exec_builtin(int is_builtin, t_tree *node, char **envp[], t_cmd_infos *cmd_infos)
{
	int		res;
	char	**cmd;
	int		fd;

	fd = manage_fds_for_builtins(cmd_infos);
	cmd = recreate_and_get_cmd(node, *envp, 0);
	if (!cmd)
		return (close_fd_builtin(fd), -1); //define error code
	if (is_builtin == 0)
		res = builtin_echo(cmd, fd);
	else if (is_builtin == 1)
		res = -1; //implement cd
	else if (is_builtin == 2)
		res = builtin_pwd(fd);
	else if (is_builtin == 3)
		res = builtin_export(cmd, envp, fd);
	else if (is_builtin == 4)
		res = builtin_unset(cmd, envp, fd);
	else if (is_builtin == 5)
		res = builtin_env(*envp, fd);
	else if (is_builtin == 6)
		res = -1; //implement exit
	else
		res = -1; //define error code
	return (close_fd_builtin(fd), free_split(cmd), res);
}
