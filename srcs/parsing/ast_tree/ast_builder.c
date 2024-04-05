/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:54:04 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/19 13:36:07 by ehickman         ###   ########.fr       */
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

static void	print_ast_error(t_token *t)
{
	if (!t)
		return ;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (t->type == T_WORD)
		ft_putstr_fd(t->content, 2);
	else if (t->type == T_PIPE)
		ft_putstr_fd("|", 2);
	else if (t->type == T_RET_FROM)
		ft_putstr_fd("<", 2);
	else if (t->type == T_RET_TO)
		ft_putstr_fd(">", 2);
	else if (t->type == T_DLESS)
		ft_putstr_fd("<<", 2);
	else if (t->type == T_DGREAT)
		ft_putstr_fd(">>", 2);
	else if (t->type == T_END)
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

t_tree	*ast_builder(t_token **t)
{
	t_tree		*ast;
	t_ast_data	*d;

	d = malloc(sizeof(t_ast_data));
	if (!d)
		return (ft_perror(), NULL);
	d->stream = malloc(sizeof(t_token *));
	if (!d->stream)
		return (free(d), ft_perror(), NULL);
	d->count = 0;
	*(d->stream) = *t;
	ast = parse_cmd_line(d);
	if ((d->stream && (*(d->stream))->type != T_END) || !ast)
		return (print_ast_error(*(d->stream)), free_ast_data(d), \
		ft_treeclear(&ast), NULL);
	free_ast_data(d);
	return (ast);
}
