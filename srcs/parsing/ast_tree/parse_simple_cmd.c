/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 08:17:22 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/17 08:18:15 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*parse_cmd_suffix(t_token **token_stream, t_tree *prev)
{
	t_tree	*suffix_node;

	suffix_node = parse_io_redirect(token_stream);
	if (!suffix_node)
		return (ft_treeclear(&prev), NULL);
	else if (suffix_node == NOT_FOUND)
	{
		if ((*token_stream)->type != T_WORD)
			return (prev);
		suffix_node = create_node(R_CMD_SUFFIX, (*token_stream)->content, NULL, NULL);
		if (!suffix_node)
			return (ft_treeclear(&prev), NULL);
		add_node_to_bottom_right(prev, suffix_node);
		consume_token(token_stream);
		return (parse_cmd_suffix(token_stream, prev));
	}
	add_node_to_bottom_left(suffix_node, prev);
	return (parse_cmd_suffix(token_stream, suffix_node));
}

t_tree	*parse_cmd_prefix(t_token **token_stream, t_tree *left)
{
	t_tree	*prefix_node;

	prefix_node = parse_io_redirect(token_stream);
	if (!prefix_node)
		return (NULL);
	else if (prefix_node == NOT_FOUND && !left)
		return (NOT_FOUND);
	else if (prefix_node == NOT_FOUND)
		return (left);
	else if (prefix_node)
		add_node_to_bottom_left(prefix_node, left);
	return (parse_cmd_prefix(token_stream, prefix_node));
}

t_tree	*parse_simple_cmd(t_token **token_stream)
{
	t_tree	*cmd_node;
	t_tree	*cmd_prefix;

	cmd_prefix = parse_cmd_prefix(token_stream, NULL);
	if (!cmd_prefix)
		return (NULL);
	if (is_token_type(*token_stream, T_WORD))
	{
		if (cmd_prefix == NOT_FOUND)
			cmd_node = create_node(R_CMD_NAME, (*token_stream)->content, NULL, NULL);
		else
			cmd_node = create_node(R_CMD_NAME, (*token_stream)->content, cmd_prefix, NULL);
		if (!cmd_node)
			return (ft_treeclear(&cmd_prefix), NULL); // malloc error
		consume_token(token_stream);
		return (parse_cmd_suffix(token_stream, cmd_node));
	}
	return (cmd_prefix);
}
