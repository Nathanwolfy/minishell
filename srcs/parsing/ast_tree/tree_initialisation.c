/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:59:02 by ehickman          #+#    #+#             */
/*   Updated: 2023/12/12 18:06:26 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/common.h"

t_ast_node	*create_node(int type, char *content, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*new;

	new = malloc(sizeof(t_ast_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = content;
	new->left = left;
	new->right = right;
	return (new);
}

t_token	*find_junction(t_token *start_token)
{
	t_token	*cursor;

	if (!start_token)
		return (NULL);
	cursor = start_token;
	while (cursor)
	{
		if (is_junction_type(cursor->type))
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

/*errno needs to be set correctly | also check if the exit status needs to be modified on specific errors*/
int	ast_tree_initialisation(t_token **line)
{
	t_ast_node	**root;
	t_ast_node	**attach;
	t_token		*next_start;
	t_token		*junction;

	root = malloc(sizeof(t_ast_node *));
	if (!root)
		return (-1);
	*root = NULL;
	attach = root;
	next_start = *line;
	while (1)
	{
		junction = find_junction(next_start);
		if (!junction)
		{
			*root = fill_tree(next_start);
			if (!*root)
				return (
		}
	}
}
