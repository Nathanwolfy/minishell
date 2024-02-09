/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:17:36 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:17:44 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	cmd_split_count(t_tree *node)
{
	int		ct;
	t_tree	*it;

	ct = 1;
	it = node;
	while (it->right && (it->right)->type == R_CMD_SUFFIX)
	{
		ct++;
		it = it->right;
	}
	return (ct);
}
