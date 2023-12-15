/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:52:55 by ehickman          #+#    #+#             */
/*   Updated: 2023/12/15 16:35:26 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/common.h"

static t_ast_node	*create_cmd_suffix_node(t_ast_node *parent, t_token *token)
{
	t_ast_node	*new;

	new = malloc(sizeof(t_ast_node));
	if (!new)
		return (NULL);
	new->parent = parent;
	new->type = S_CMD_SUF;
	new->content = token->content;
	new->left = NULL;
	if (token->next && token->next->type == T_WORD)
	{
		new->right = create_cmd_suffix_node(new, token->next);
		if (!new->right)
			return (free(new), NULL);
	}
	else
		new->right = NULL;
	return (new);
}

static t_ast_node	*create_sub_cmd_node(t_ast_node *parent, t_token *token)
{
	t_ast_node	*new;

	new = malloc(sizeof(t_ast_node));
	if (!new)
		return (NULL);
	new->parent = parent;
	new->type = S_CMD;
	new->left = malloc(sizeof(t_ast_node));
	if (!new->left)
		return (free(new), NULL);
	new->left->parent = new;
	new->left->type = S_CMD_NAME;
	new->left->content = token->content;
	if (token->next && token->next->type == T_WORD)
	{
		new->right = create_cmd_suffix_node(new, token->next);
		if (!new->right)
			return (free(new->left), free(new), NULL);
	}
	else
		new->right = NULL;
	return (new);
}

t_ast_node	*create_cmd_node(t_ast_node *parent, t_token *token)
{
	t_ast_node	*new;
	t_ast_node	*cmd_node;

	new = malloc(sizeof(t_ast_node));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->type = S_CMP;
	new->parent = parent;
	new->right = create_sub_cmd_node(new, token);
}
