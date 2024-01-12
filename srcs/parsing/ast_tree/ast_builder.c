/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:54:04 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/12 15:06:17 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_tree	*ast_builder(t_token **t)
{
	t_tree	*ast;
	t_token	**token_stream;

	token_stream = malloc(sizeof(t_token *));
	if (!token_stream)
		return (NULL);
	*token_stream = *t;
	ast = parse_cmd_line(token_stream);
	return (ast);
}
