/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:47:42 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/14 16:54:35 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*add_node_to_bottom_left(t_tree *main, t_tree *new_node)
{
	t_tree	*cursor;

	if (!main && !new_node)
		return (NULL);
	if (!main && new_node)
		return (new_node);
	cursor = main;
	while (cursor->left != NULL)
		cursor = cursor->left;
	cursor->left = new_node;
	return (main);
}
