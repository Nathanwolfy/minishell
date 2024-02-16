/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:38:21 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 14:07:48 by ehickman         ###   ########.fr       */
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

int	simple_quotes_loop(char *line, int *k, int *table)
{
	table[*k] = -1;
	*k += 1;
	while (line[*k] && line[*k] != SQUOTE)
	{
		table[(*k)] = 1;
		*k += 1;
	}
	if (line[*k] == SQUOTE)
	{
		table[*k] = -1;
		*k += 1;
	}
	else if (!line[*k])
		return (-1);
	return (0);
}

int	double_quotes_loop(char *line, int *k, int *table)
{
	table[*k] = -1;
	*k += 1;
	while (line[*k] && line[*k] != DQUOTE)
	{
		table[(*k)] = 1;
		*k += 1;
	}
	if (line[*k] == DQUOTE)
	{
		table[*k] = -1;
		*k += 1;
	}
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
		if (line[k] == SQUOTE)
		{
			if (simple_quotes_loop(line, &k, table) < 0)
				return (-1);
		}
		else if (line[k] == DQUOTE)
		{
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
