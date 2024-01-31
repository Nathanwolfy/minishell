/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:38:21 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/31 13:25:48 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
0 : nothing
-1 : error in simple quotes
-2 : error in double quotes
-3 : error in malloc
-4 : missing line
*/

int	print_error_lexer(int code)
{
	if (code == -1)
		ft_putendl_fd("minishell: syntax error in simple quotes", \
		STDERR_FILENO);
	else if (code == -2)
		ft_putendl_fd("minishell: syntax error in double quotes", \
		STDERR_FILENO);
	else if (code != 0)
	{
		print_error_from_errno();
		errno = 0;
	}
	return (code);
}

int	simple_quotes_loop(char *line, int *k, int *table)
{
	while (line[*k] && line[*k] != '\'')
		table[(*k)++] = 1;
	if (line[*k] == '\'')
		table[(*k)++] = 1;
	else if (!line[*k])
		return (-1);
	return (0);
}

int	double_quotes_loop(char *line, int *k, int *table)
{
	while (line[*k] && line[*k] != '\"')
		table[(*k)++] = 1;
	if (line[*k] == '\"')
		table[(*k)++] = 1;
	else if (!line[*k])
		return (-2);
	return (0);
}

int	quote_sequence(int *table, char *line)
{
	int	k;

	k = 0;
	while (line[k])
	{
		if (line[k] == '\'')
		{
			table[k++] = 1;
			if (simple_quotes_loop(line, &k, table) < 0)
				return (-1);
		}
		else if (line[k] == '\"')
		{
			table[k++] = 1;
			if (double_quotes_loop(line, &k, table) < 0)
				return (-2);
		}
		else
			k++;
	}
	return (0);
}

int	operator_sequence(int *table, char *line)
{
	int	k;

	k = 0;
	while (line[k])
	{
		if (line[k] == '|')
			table[k++] = 3;
		else if (line[k] == '<' && line[k + 1] != '<')
			table[k++] = 5;
		else if (line[k] == '>' && line[k + 1] != '>')
			table[k++] = 6;
		else if (line[k] == '<' && line[k + 1] == '<')
		{
			table[k++] = 7;
			table[k++] = 7;
		}
		else if (line[k] == '>' && line[k + 1] == '>')
		{
			table[k++] = 8;
			table[k++] = 8;
		}
		else
			k++;
	}
	return (0);
}
