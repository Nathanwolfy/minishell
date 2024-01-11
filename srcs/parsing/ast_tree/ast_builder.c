/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:54:04 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/11 18:22:23 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/common.h"

void	consume_token(t_token **token_stream)
{
	if (*token_stream)
		*token_stream = (*token_stream)->next;
}

t_tree	*ast_builder(t_token **t)
{
	t_tree	*ast;
	t_token	**token_stream;

	token_stream = malloc(sizeof(t_token *));
	if (!token_stream)
		return (NULL);
	*token_stream = *t;
	ast = parse_cmd_line(token_stream);
}
