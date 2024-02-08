/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:05:33 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/08 10:15:50 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	builtin_pwd(int fd)
{
	char	buffer[PATH_MAX];
	size_t	size;

	size = PATH_MAX;
	if (getcwd(buffer, size) == NULL)
		return (1);
	ft_putendl_fd(buffer, fd);
	return (0);
}
