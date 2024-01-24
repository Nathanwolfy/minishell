/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:41:23 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/23 10:34:27 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	add_node_to_bottom_right(t_tree *main, t_tree *new_node)
{
	t_tree	*target;

	if (!main)
		return ;
	target = main;
	while (target->right != NULL)
		target = target->right;
	target->right = new_node;
}

int	is_io_file(t_token *t)
{
	if (t->type == T_RET_TO || t->type == T_RET_FROM || t->type == T_DGREAT)
		return (1);
	return (0);
}

t_tree	*create_node(int type, char *content, t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = type;
	if (content)
	{
		node->content = ft_strdup(content);
		if (!node->content)
			return (NULL);
	}
	else
		node->content = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

void	consume_token(t_ast_data *d)
{
	if (!d)
		return ;
	if (*(d->stream))
	{
		*(d->stream) = (*(d->stream))->next;
		d->count += 1;
	}
}

int	is_token_type(t_token *t, int type)
{
	if (t && t->type == type)
		return (1);
	return (0);
}
