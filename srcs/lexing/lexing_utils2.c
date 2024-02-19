/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:21:50 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/17 16:22:26 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	other_chars_sequence(int *table, char *line)
{
	int	k;

	k = 0;
	while (line[k])
	{
		if (!(line[k] == ' ' || line[k] == '\t') && !table[k])
			table[k] = 1;
		k++;
	}
	return (0);
}

int	build_token(t_token **token, int type, int *k, char *content)
{
	t_token	*new_token;

	new_token = ft_tokennew(content, type);
	if (!new_token)
		return (-3);
	ft_tokenadd_back(token, new_token);
	if (type == T_DGREAT || type == T_DLESS)
		(*k)++;
	if (type != T_WORD)
		(*k)++;
	return (0);
}

int	print_error_lexer(int code, int *exit_status)
{
	if (code == -1)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `\'\'", \
		STDERR_FILENO);
		*exit_status = 1;
	}
	else if (code == -2)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `\"\'", \
		STDERR_FILENO);
		*exit_status = 1;
	}
	else if (code != 0)
	{
		ft_perror();
		*exit_status = errno;
		errno = 0;
	}
	return (code);
}
