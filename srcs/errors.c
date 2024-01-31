/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:00:36 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/31 13:19:52 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	print_error_from_errno(void)
{
	if (errno != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (errno);
}