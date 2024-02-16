/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:06:18 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 18:56:10 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
0 : success
1 : all errors from errno
127 : command not found
else : unknown error
*/

int	print_error_cmd(char *cmd, int status, \
t_malloc_data *data, t_cmd_infos *infos)
{
	(void)cmd;
	if (status == 127)
		status = 127;
	else if (status == 126)
		status = 126;
	else if (status == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(status), STDERR_FILENO);
	}
	else
	{
		ft_putendl_fd("minishell: unknown error", STDERR_FILENO);
		status = 1;
	}
	free_data_infos(data, infos);
	return (status);
}

void	no_such_file(t_cmd_infos *infos, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	infos->status = 127;
	infos->error = 1;
}

void	cmd_not_found(t_cmd_infos *infos, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	infos->status = 127;
	infos->error = 1;
}

int	check_unknown_error(int status)
{
	if (status == 2)
		return (print_error_cmd(NULL, status, NULL, NULL), 1);
	else
		return (status);
}

int	print_missing_ast(void)
{
	ft_putendl_fd("minishell: interpreter: missing ast", STDERR_FILENO);
	return (1);
}
