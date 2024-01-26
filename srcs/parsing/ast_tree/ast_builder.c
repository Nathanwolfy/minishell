/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:54:04 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/26 10:10:28 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_ast_data(t_ast_data *d)
{
	if (!d)
		return ;
	if (d->stream)
		free(d->stream);
	free(d);
}

t_tree	*ast_builder(t_token **t)
{
	t_tree		*ast;
	t_ast_data	*d;

	d = malloc(sizeof(t_ast_data));
	if (!d)
		return (NULL);
	d->stream = malloc(sizeof(t_token *));
	if (!d->stream)
		return (free(d), NULL);
	d->count = 0;
	d->start = 1;
	*(d->stream) = *t;
	ast = parse_cmd_line(d);
	free_ast_data(d);
	return (ast);
}
