/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:18:25 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/14 15:33:34 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*parse_dless(t_ast_data *d)
{
	t_tree	*node;

	node = create_node(R_IO_FILE_DLESS, NULL, NULL, NULL);
	if (!node)
		return (NULL);
	consume_token(d);
	if (!is_token_type(*(d->stream), T_WORD))
		return (NOT_FOUND);
	node->right = create_node(R_HERE_END, (*(d->stream))->content, NULL, NULL);
	if (!node->right)
		return (ft_treeclear(&node), NULL);
	return (node);
}

t_tree	*create_redirect_node(t_ast_data *d)
{
	t_tree	*node;

	if (is_token_type(*(d->stream), T_RET_TO))
		node = create_node(R_IO_FILE_TO, NULL, NULL, NULL);
	else if (is_token_type(*(d->stream), T_RET_FROM))
		node = create_node(R_IO_FILE_FROM, NULL, NULL, NULL);
	else if (is_token_type(*(d->stream), T_DGREAT))
		node = create_node(R_IO_FILE_DGREAT, NULL, NULL, NULL);
	else if (is_token_type(*(d->stream), T_DLESS))
		node = parse_dless(d);
	else
		return (NOT_FOUND);
	if (!node)
		return (NULL);
	else if (node == NOT_FOUND)
		return (NOT_FOUND);
	consume_token(d);
	return (node);
}

t_tree	*parse_io_file_arg(t_ast_data *d, t_tree *prev)
{
	if (prev->type != R_IO_FILE_DLESS && is_token_type(*(d->stream), T_WORD))
	{
		prev->right = create_node(R_FILENAME, (*(d->stream))->content, NULL, \
		NULL);
		if (!prev->right)
			return (ft_treeclear(&prev), NULL);
		consume_token(d);
	}
	else if (prev->type != R_IO_FILE_DLESS && !is_token_type(*(d->stream), \
		T_WORD))
		return (ft_treeclear(&prev), NULL);
	return (prev);
}

t_tree	*parse_io_file(t_ast_data *d)
{
	t_tree	*io_file_node;

	if (!*(d->stream))
		return (NOT_FOUND);
	io_file_node = create_redirect_node(d);
	if (!io_file_node)
		return (NULL);
	else if (io_file_node == NOT_FOUND)
		return (NOT_FOUND);
	return (parse_io_file_arg(d, io_file_node));
}

t_tree	*parse_io_redirect(t_ast_data *d)
{
	if (*(d->stream) && is_io_file(*(d->stream)))
		return (parse_io_file(d));
	else
		return (NOT_FOUND);
}
