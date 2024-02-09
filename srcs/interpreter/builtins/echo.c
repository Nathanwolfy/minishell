/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:49:38 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/09 12:34:19 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	check_option_n(char *suffix)
{
	if (!suffix)
		return (1);
	if (suffix[0] == '-' && suffix[1] == 'n' && suffix[2] == '\0')
		return (0);
	else
		return (1);
}

int	builtin_echo(char **cmd, int fd) //what happens if invalid option
{
	int	option_n;
	int	i;

	if (!cmd || !*cmd)
		return (1); //define clean error codes
	i = 1;
	option_n = check_option_n(cmd[1]);
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
