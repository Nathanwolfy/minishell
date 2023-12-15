/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:20:56 by ehickman          #+#    #+#             */
/*   Updated: 2023/12/15 16:13:17 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/common.h"

t_ast_node	*create_ast_node(t_ast_node *parent, t_token *token)
{
	t_ast_node	*new;

	if (!token)
		return (NULL);
	new = NULL;
	if (token->type == T_CMD)
		new = create_cmd_node(parent, token); // to create
	else if (token->type == T_PIPE)
		new = create_pipe_node(parent, token); // to create
	else if (token->type == T_REDIRECT_IN)
		new = create_r_in_node(parent, token); // to create
	else if (token->type == T_REDIRECT_OUT)
		new = create_r_out_node(parent, token); // to create
	else if (token->type == T_HERE_DOC)
		new = create_here_doc_node(parent, token); // to create
	else if (token->type == T_REDIRECT_APP)
		new = create_redir_node(parent, token); // to create
	return (new);
}

t_ast_node	*build_line(t_ast_node *parent, t_token *token)
{
	t_ast_node	*root;
	t_ast_node	*new;
	t_ast_node	*new_parent;
	t_token		*cursor;

	if (!token)
		return (NULL);
	cursor = get_last_of_line(token);// to create
	new_parent = parent;
	root = NULL;
	while (cursor && cursor->type != T_PIPE)
	{
		if (cursor->type != T_WORD)
		{
			new = create_ast_node(new_parent, cursor);// to check
			if (!root)
			{
				root = new;
				new_parent = root;
			}
			else
			{
				new_parent->left = new;
				new_parent = new;
			}
		}
		cursor = cursor->prev;
	}
	return (root);
}

t_ast_node	*build_ast(t_ast_node *parent, t_token *line)
{
	t_ast_node	*root;
	t_token		*pipe;
	t_token		*left;
	t_token		*right;

	pipe = find_pipe(line);
	root = NULL;
	left = NULL;
	right = NULL;
	if (pipe)
	{
		root = create_ast_node(parent, line);
		if (!root)
			return (NULL);
		split_on_pipe(&left, &right, pipe, line); // right will simply point to the next token and left to the first token before the pipe
		root->right = build_line(root, right); // to check
		root->left = build_ast(root, left); // to check
	}
	else
	{
		root = build_line(parent, line); // needs to check for errors
	}
	return (root);
}
