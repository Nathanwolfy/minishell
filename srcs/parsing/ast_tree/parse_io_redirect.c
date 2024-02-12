/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:18:25 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:39 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*parse_simple_cmd_prime(t_ast_data *d)
{
	t_tree	*node;
	t_tree	*new_node;

	if (!*(d->stream) || !is_token_type(*(d->stream), T_WORD))
		return (NOT_FOUND);
	node = create_node(R_CMD_NAME, (*(d->stream))->content, NULL, NULL);
	if (!node)
		return (NULL);
	consume_token(d);
	while (is_token_type(*(d->stream), T_WORD))
	{
		new_node = create_node(R_CMD_SUFFIX, (*(d->stream))->content, NULL, NULL);
		if (!new_node)
			return (ft_treeclear(&node), NULL);
		add_node_to_bottom_right(node, new_node);
		consume_token(d);
	}
	return (node);
}

t_tree	*parse_infile(t_ast_data *d)
{
	t_tree	*node;
	t_tree	*left;

	node = NULL;
	if ((*(d->stream))->type == T_RET_TO)
		node = create_node(R_IO_FILE_TO, NULL, NULL, NULL);
	else if ((*(d->stream))->type == T_RET_FROM)
		node = create_node(R_IO_FILE_FROM, NULL, NULL, NULL);
	if (!node)
		return (NULL);
	consume_token(d);
	if (!is_token_type(*(d->stream), T_WORD))
		return (ft_treeclear(&node), NOT_FOUND);
	node->right = create_node(R_FILENAME, (*(d->stream))->content, NULL, NULL);
	if (!node->right)
		return (ft_treeclear(&node), NULL);
	consume_token(d);
	left = parse_simple_cmd_prime(d);
	if (left == NULL)
		return (ft_treeclear(&node), NULL);
	else if (left == NOT_FOUND)
		return (node);
	node->left = left;
	return (node);
}

t_tree	*parse_io_file_arg(t_ast_data *d, t_tree *prev)
{
	t_tree *new_node;

	if (!prev->left || prev->left->type != R_CMD_NAME)
		return (ft_treeclear(&prev), NULL);
	while (is_token_type(*(d->stream), T_WORD))
	{
		new_node = create_node(R_CMD_SUFFIX, (*(d->stream))->content, NULL, NULL);
		if (!new_node)
			return (ft_treeclear(&prev), NULL);
		add_node_to_bottom_right(prev->left, new_node);
		consume_token(d);
	}
	return (prev);
}

t_tree	*parse_io_file(t_ast_data *d)
{
	t_tree	*io_file_node;

	if (!*(d->stream))
		return (NOT_FOUND);
	if (((*(d->stream))->type == T_RET_TO || (*(d->stream))->type == T_RET_FROM) && d->start)
		return (parse_infile(d));
	else if ((*(d->stream))->type == T_RET_TO)
		io_file_node = create_node(R_IO_FILE_TO, NULL, NULL, NULL);
	else if ((*(d->stream))->type == T_RET_FROM)
		io_file_node = create_node(R_IO_FILE_FROM, NULL, NULL, NULL);
	else if ((*(d->stream))->type == T_DGREAT)
		io_file_node = create_node(R_IO_FILE_DGREAT, NULL, NULL, NULL);
	else
		return (NOT_FOUND);
	if (!io_file_node)
		return (NULL);
	consume_token(d);
	if (!is_token_type((*(d->stream)), T_WORD))
		return (ft_treeclear(&io_file_node), NOT_FOUND);
	io_file_node->right = create_node(R_FILENAME, (*(d->stream))->content, NULL, NULL);
	if (!io_file_node->right)
		return (ft_treeclear(&io_file_node), NULL);
	consume_token(d);
	return (io_file_node);
}

t_tree	*parse_io_here(t_ast_data *d)
{
	t_tree	*io_here_node;

	io_here_node = create_node(R_IO_FILE_DLESS, NULL, NULL, NULL);
	if (!io_here_node)
		return (NULL);
	consume_token(d);
	if (!is_token_type(*(d->stream), T_WORD))
		return (ft_treeclear(&io_here_node), NOT_FOUND);
	io_here_node->right = create_node(R_HERE_END, (*(d->stream))->content, NULL, NULL);
	if (!io_here_node->right)
		return (ft_treeclear(&io_here_node), NULL);
	consume_token(d);
	return (io_here_node);
}

t_tree	*parse_io_redirect(t_ast_data *d)
{
	if (*(d->stream) && (*(d->stream))->type == T_DLESS)
		return (parse_io_here(d));
	else if (*(d->stream) && is_io_file(*(d->stream)))
		return (parse_io_file(d));
	else
		return (NOT_FOUND);
}
