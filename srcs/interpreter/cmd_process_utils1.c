/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:21:25 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/14 16:50:08 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	f_ok(char *file)
{
	return (access(file, F_OK));
}

int	x_ok(char *file)
{
	return (access(file, X_OK));
}

int	fnot_ok_xok(char *file)
{
	return (!f_ok(file) && x_ok(file));
}

void	deny(t_cmd_infos *infos)
{
	infos->status = 126;
}

void	err(t_cmd_infos *infos)
{
	infos->status = 1;
}
