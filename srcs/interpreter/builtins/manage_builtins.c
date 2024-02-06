/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:52:11 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/05 16:27:55 by nlederge         ###   ########.fr       */
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
		if (ft_strcmp(cmd, builtins[i]) == 0 && ft_strlen(cmd) == ft_strlen(builtins[i]))
			return (i);
		i++;
	}
	return (-1); //define error code
}

int	exec_builtin(int is_builtin, t_tree *node, char *envp[])
{
	int		res;
	char	**cmd;

	cmd = recreate_and_get_cmd(node, envp, 0);
	if (!cmd)
		return (-1); //define error code
	if (is_builtin == 0)
		res = builtin_echo(cmd);
	else if (is_builtin == 1)
		res = builtin_cd(cmd, envp);
	else if (is_builtin == 2)
		res = builtin_pwd();
	else if (is_builtin == 3)
		res = builtin_export(cmd, envp);
	else if (is_builtin == 4)
		res = builtin_unset(cmd, envp);
	else if (is_builtin == 5)
		res = builtin_env(envp);
	else if (is_builtin == 6)
		res = builtin_exit(cmd);
	else
		res = -1; //define error code
	return (res);
}