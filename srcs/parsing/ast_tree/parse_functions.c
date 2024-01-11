/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:33:30 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/11 18:17:11 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/common.h"

t_tree	*parse_io_file(t_token **token_stream)
{
	t_tree	*io_file_node;

	if ((*token_stream)->type == T_RET_TO)
		io_file_node = create_node(R_IO_FILE, ">", NULL, NULL);
	else if ((*token_stream)->type == T_RET_FROM)
		io_file_node = create_node(R_IO_FILE, "<", NULL, NULL);
	else if ((*token_stream)->type == T_DGREAT)
		io_file_node = create_node(R_IO_FILE, ">>", NULL, NULL);
	if (!io_file_node)
		return (NULL);
	consume_token(token_stream);
	if (!is_token_type((*token_stream), T_WORD))
		return (free(io_file_node), NULL); //differenciate with malloc
	io_file_node->right = create_node(R_FILENAME, (*token_stream)->content, NULL, NULL);
	if (!io_file_node->right)
		return (free(io_file_node), NULL);
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
		return (free(io_here_node), NULL); // differenciate between malloc and not found
	io_here_node->right = create_node(R_HERE_END, (*token_stream)->content, NULL, NULL);
	if (!io_here_node->right)
		return (free(io_here_node), NULL);
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
		return (NULL);
}

/*t_tree	*parse_cmd_suffix(t_token **token_stream, t_tree *prev)
{
	t_tree	*suffix_node;

	if (is_token_type((*token_stream), T_WORD))
	{
		if (!prev)
			return (NULL); // diff from malloc
		suffix_node = create_node(R_CMD_WORD, (*token_stream)->content, NULL, NULL);
		if (!suffix_node)
			return (NULL);
		prev->right = suffix_node;
		consume_token(token_stream);
		if (is_token_type(*token_stream, T_WORD))
			suffix_node->right = parse_cmd_suffix(token_stream,
		return (parse_cmd_suffix(token_stream, suffix_node));
	{
	else
	{
		suffix_node = parse_io_redirect(token_stream);
		if (!suffix_node)
			return (prev); // diff from malloc
		suffix_node->left = prev;
		return (suffix_node);
	}
	return (su
}*/

t_tree	*parse_cmd_prefix(t_token **token_stream, t_tree *left)
{
	t_tree	*prefix_node;

	prefix_node = parse_io_redirect(token_stream);
	if (prefix_node)
		prefix_node->left = left;
	else
		return (left); // differenciate between malloc error and no prefix
	return (parse_cmd_prefix(token_stream, prefix_node));
}

t_tree	*parse_simple_cmd(t_token **token_stream)
{
	t_tree	*cmd_node;
	t_tree	*cmd_prefix;

	cmd_prefix = parse_cmd_prefix(token_streami, NULL); // differenciate between malloc error and no prefix
	if (is_token_type(*token_stream, T_WORD))
	{
		cmd_node = create_node(R_CMD_NAME, (*token_stream)->content, cmd_prefix, NULL);
		if (!cmd_node)
			return (free_tree(cmd_prefix), NULL); // malloc error
		consume_token(token_stream);
		return (parse_cmd_suffix(token_stream, cmd_node));
	}
	else if (!cmd_prefix)
		return (NULL); //put error msg here
	return (cmd_prefix);
}

t_tree	*parse_pipe_sequence_prime(t_token **token_stream, t_tree *left)
{
	t_tree	*pipe_node;

	pipe_node = create_node(R_PIPE_SEQUENCE, NULL, left, NULL);
	if (!pipe_node)
		return(free_tree(left), NULL); // malloc error
	consume_token(d);
	pipe_node->right = parse_simple_cmd(d);
	if (!pipe_node->right)
		return (free_tree(pipe_node), NULL);
	if (is_token_type(*token_stream, T_PIPE)
		return (parse_pipe_sequence_prime(d, pipe_node));
	return (pipe_node);
}

t_tree	*parse_pipe_sequence(t_token **token_stream)
{
	t_tree	*a;

	a = parse_simple_cmd(d);
	if (!a)
		return (NULL);
	if (is_token_type(*token_stream, T_PIPE))
		return (parse_pipe_sequence_prime(d, a));
}

t_tree	*parse_cmd_sequence(t_token **token_stream)
{
	t_tree	*ast;

	ast = parse_pipe_sequence(d);
	//	if (is_token_type(d->*(token_stream), '&&') FOR BONUS
	return (ast);
}

t_tree	*parse_cmd_line(t_token **token_stream)
{
	t_tree	*ast;

	ast = parse_cmd_sequence(d);
	if (is_token_type(*token_stream, T_END))
		return (ast);
	return (NULL);	// maybe needs to be freed
}