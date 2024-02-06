/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:22:34 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/06 17:48:56 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	builtin_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], fd);
		i++;
	}
	return (0);
}
