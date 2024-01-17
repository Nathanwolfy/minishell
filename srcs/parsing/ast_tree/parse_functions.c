/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:33:30 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/17 08:20:09 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*parse_pipe_sequence_prime(t_token **token_stream, t_tree *left)
{
	t_tree	*pipe_node;

	pipe_node = create_node(R_PIPE_SEQUENCE, NULL, left, NULL);
	if (!pipe_node)
		return(ft_treeclear(&left), NULL); // malloc error
	consume_token(token_stream);
	pipe_node->right = parse_simple_cmd(token_stream);
	if (!pipe_node->right)
		return (ft_treeclear(&pipe_node), NULL);
	if (is_token_type(*token_stream, T_PIPE))
		return (parse_pipe_sequence_prime(token_stream, pipe_node));
	return (pipe_node);
}

t_tree	*parse_pipe_sequence(t_token **token_stream)
{
	t_tree	*a;

	a = parse_simple_cmd(token_stream);
	if (!a)
		return (NULL);
	else if (a == NOT_FOUND)
		return (NOT_FOUND);
	if (is_token_type(*token_stream, T_PIPE))
		return (parse_pipe_sequence_prime(token_stream, a));
	return (a);
}

t_tree	*parse_cmd_sequence(t_token **token_stream)
{
	t_tree	*ast;

	ast = parse_pipe_sequence(token_stream);
	//	if (is_token_type(d->*(token_stream), '&&') FOR BONUS
	return (ast);
}

t_tree	*parse_cmd_line(t_token **token_stream)
{
	t_tree	*ast;

	ast = parse_cmd_sequence(token_stream);
	if (is_token_type(*token_stream, T_END))
		return (ast);
	return (ast);	// maybe needs to be freed
}
