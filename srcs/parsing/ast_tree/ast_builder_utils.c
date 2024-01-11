/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:41:23 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/11 17:41:32 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/common.h"

int	is_io_file(t_token *t)
{
	if (t->type == T_RET_TO || t->type == T_RET_FROM || t->type == T_DGREAT)
		return (1);
	return (0);
}

t_tree	*create_node(int type, char *content, t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
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
	d->(*token_stream) = d->(*token_stream)->next;
	if (d->(*token_stream))
		d->lookahead = d->(*token_stream)->next;
	else
		d->lookahead = NULL;
}

int	is_token_content(t_token *t, char *content)
{
	int	i;

	i = 0;
	while (t->content[i] || content[i])
	{
		if (t->content[i] != content[i])
			return (0);
	}
	return (1);
}

int	is_token_type(t_token *t, int type)
{
	if (token->type == type)
		return (1);
	return (0);
}
