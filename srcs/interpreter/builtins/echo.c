/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:49:38 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/06 18:00:53 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	check_option_n(char **cmd)
{
	if (!cmd[0])
		return (1);
	if (cmd[0][0] == '-' && cmd[0][1] == 'n' && !cmd[0][2])
		return (0);
	else
		return (1);
}

int	builtin_echo(char **cmd, int fd) //what happens if invalid option
{
	int	option_n;
	int	i;

	if (!cmd)
		return (-1); //define clean error codes
	i = 1;
	option_n = check_option_n(cmd);
	while (cmd[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(cmd[i], fd);
		i++;
	}
	if (option_n)
		ft_putchar_fd('\n', fd);
	return (0);
}
