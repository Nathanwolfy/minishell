/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:49:38 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/12 15:19:04 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	check_option_n(char *suffix)
{
	int	i;

	if (suffix[0] == '-')
	{
		i = 1;
		while (suffix[i] && suffix[i] == 'n')
			i++;
		if (i > 1 && suffix[i] == '\0')
			return (1);
	}
	return (0);
}

int	builtin_echo(char **cmd, int fd)
{
	int	option_n;
	int	i;
	int	has_printed;

	if (!cmd || !*cmd)
		return (1);
	i = 1;
	option_n = 0;
	has_printed = 0;
	while (cmd[i])
	{
		if (!has_printed && check_option_n(cmd[i]))
		{
			option_n = 1;
			i++;
			continue ;
		}
		if (has_printed == 1)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(cmd[i++], fd);
		has_printed = 1;
	}
	if (!option_n)
		ft_putchar_fd('\n', fd);
	return (0);
}
