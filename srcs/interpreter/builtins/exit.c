/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:08:59 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/14 17:48:34 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
check for too many arguments
convert exit code to a number between 0 and 255
*/

static int	get_code(char **cmd)
{
	(void)cmd;
	return (0);
}

int	builtin_exit(char **cmd, t_malloc_data *data, t_cmd_infos *infos)
{
	int	code;

	code = get_code(cmd);
	if (code < 0)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		code = 1;
	}
	free_data_infos(data, infos);
	ft_putendl_fd("exit", STDERR_FILENO);
	return (exit_return(code));
}
