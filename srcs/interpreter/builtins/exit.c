/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:08:59 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/15 18:16:13 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
check for too many arguments
convert exit code to a number between 0 and 255
*/

static int	get_split_size(char **cmd)
{
	int	ct;

	ct = 0;
	if (!cmd)
		return (0);
	while (cmd[ct])
		ct++;
	return (ct);
}

static int	ft_isnumber(char *str)
{
	int		ct;

	ct = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		ct++;
	while (str[ct])
	{
		if (str[ct] < '0' || str[ct] > '9')
			return (0);
		ct++;
	}
	return (1);
}

static int	get_code(char **cmd)
{
	int		ct;

	ct = get_split_size(cmd);
	if (ct != 2)
		return (-1);
	if (ft_isnumber(cmd[1]) == 0)
		return (-2);
	return ((int)((unsigned char)ft_atoi(cmd[1])));
}

int	builtin_exit(char **cmd, t_malloc_data *data, t_cmd_infos *infos)
{
	int	code;

	code = get_code(cmd);
	if (code == -1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		code = 1;
	}
	else if (code == -2)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		code = 2;
	}
	free_data_infos(data, infos);
	ft_putendl_fd("exit", STDERR_FILENO);
	return (exit_return(code));
}
