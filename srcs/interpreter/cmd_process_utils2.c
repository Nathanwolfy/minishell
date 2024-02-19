/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:21:25 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/17 16:28:35 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	f_ok(char *file)
{
	return (access(file, F_OK));
}

int	x_ok(char *file)
{
	return (access(file, X_OK));
}

int	fnot_ok_xok(char *file)
{
	return (!f_ok(file) && x_ok(file));
}

int	is_directory(char *cmdname, t_cmd_infos *infos)
{
	struct stat	path_stat;

	if (stat(cmdname, &path_stat) != 0)
		return (0);
	else if (S_ISDIR(path_stat.st_mode) && ft_strchr(cmdname, '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmdname, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		infos->status = 126;
		infos->error = 1;
		return (1);
	}
	return (0);
}
