/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:05:33 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/06 14:15:33 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	builtin_pwd(void)
{
	char	buffer[PATH_MAX];
	size_t	size;

	size = PATH_MAX;
	if (getcwd(buffer, size) == NULL)
		return (-1);
	printf("%s\n", buffer);
	return (0);
}
