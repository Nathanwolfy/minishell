/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:49:38 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/06 13:58:21 by ehickman         ###   ########.fr       */
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

int	builtin_echo(char **cmd)
{
	int	option_n;
	int	i;

	if (!cmd)
		return (-1);
	i = 0;
	option_n = check_option_n(cmd);
	while (cmd[i])
	{
		if (i > 0)
			write (1, " ", 1);
		printf("%s", cmd[i]);
		i++;
	}
	if (option_n)
		write (1, "\n", 1);
	return (0);
}
