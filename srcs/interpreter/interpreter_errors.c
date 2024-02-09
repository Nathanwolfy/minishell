/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:06:18 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 11:59:57 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
0 : success
1 : all errors from errno
127 : command not found
else : unknown error
*/

int	print_error_cmd(int status)
{
	if (status == 127)
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	else if (status == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(status), STDERR_FILENO);
	}
	else
		ft_putstr_fd("minishell: unknown error", STDERR_FILENO);
	return (status);
}

int check_unknown_error(int status)
{
	if (status == 2)
		return (print_error_cmd(status), 1);
	else
		return (status);
}