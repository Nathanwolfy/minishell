/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:18:25 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/17 08:19:28 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*parse_simple_cmd_prime(t_token **token_stream)
{
	t_tree	*node;
	t_tree	*new_node;

	if (!*token_stream || !is_token_type(*token_stream, T_WORD))
		return (NOT_FOUND);
	node = create_node(R_CMD_NAME, (*token_stream)->content, NULL, NULL);
	if (!node)
		return (NULL);
	consume_token(token_stream);
	while (is_token_type(*token_stream, T_WORD))
	{
		new_node = create_node(R_CMD_SUFFIX, (*token_stream)->content, NULL, NULL);
		if (!new_node)
			return (ft_treeclear(&node), NULL);
		add_node_to_bottom_right(node, new_node);
		consume_token(token_stream);
	}
	return (node);
}

t_tree	*parse_infile(t_token **token_stream)
{
	t_tree	*node;
	t_tree	*left;

	node = NULL;
	if ((*token_stream)->type == T_RET_TO)
		node = create_node(R_IO_FILE_TO, NULL, NULL, NULL);
	else if ((*token_stream)->type == T_RET_FROM)
		node = create_node(R_IO_FILE_FROM, NULL, NULL, NULL);
	if (!node)
		return (NULL);
	consume_token(token_stream);
	if (!is_token_type(*token_stream, T_WORD))
		return (ft_treeclear(&node), NOT_FOUND);
	node->right = create_node(R_FILENAME, (*token_stream)->content, NULL, NULL);
	if (!node->right)
		return (ft_treeclear(&node), NULL);
	consume_token(token_stream);
	left = parse_simple_cmd_prime(token_stream);
	if (left == NULL)
		return (ft_treeclear(&node), NULL);
	else if (left == NOT_FOUND)
		return (node);
	node->left = left;
	return (node);
}

t_tree	*parse_io_file(t_token **token_stream)
{
	t_tree	*io_file_node;

	if (!*token_stream)
		return (NOT_FOUND);
	if ((*token_stream)->type == T_RET_TO)
		return (parse_infile(token_stream));
	else if ((*token_stream)->type == T_RET_FROM)
		return (parse_infile(token_stream));
	else if ((*token_stream)->type == T_DGREAT)
		io_file_node = create_node(R_IO_FILE_DGREAT, NULL, NULL, NULL);
	else
		return (NOT_FOUND);
	if (!io_file_node)
		return (NULL);
	consume_token(token_stream);
	if (!is_token_type((*token_stream), T_WORD))
		return (ft_treeclear(&io_file_node), NOT_FOUND);
	io_file_node->right = create_node(R_FILENAME, (*token_stream)->content, NULL, NULL);
	if (!io_file_node->right)
		return (ft_treeclear(&io_file_node), NULL);
	consume_token(token_stream);
	return (io_file_node);
}

t_tree	*parse_io_here(t_token **token_stream)
{
	t_tree	*io_here_node;

	io_here_node = create_node(R_IO_HERE, NULL, NULL, NULL);
	if (!io_here_node)
		return (NULL);
	consume_token(token_stream);
	if (!is_token_type(*token_stream, T_WORD))
		return (ft_treeclear(&io_here_node), NOT_FOUND);
	io_here_node->right = create_node(R_HERE_END, (*token_stream)->content, NULL, NULL);
	if (!io_here_node->right)
		return (ft_treeclear(&io_here_node), NULL);
	consume_token(token_stream);
	return (io_here_node);
}

t_tree	*parse_io_redirect(t_token **token_stream)
{
	if (*token_stream && (*token_stream)->type == T_DLESS)
		return (parse_io_here(token_stream));
	else if (*token_stream && is_io_file(*token_stream))
		return (parse_io_file(token_stream));
	else
		return (NOT_FOUND);
}
