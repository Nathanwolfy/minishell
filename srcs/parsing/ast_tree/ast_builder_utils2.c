/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:47:42 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/15 10:51:07 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	add_node_to_bottom_left(t_tree *main, t_tree *new_node)
{
	t_tree	*cursor;

	cursor = main;
	while (cursor->left != NULL)
		cursor = cursor->left;
	cursor->left = new_node;
}
