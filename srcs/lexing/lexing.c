/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:58:01 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/31 13:26:19 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	other_chars_sequence(int *table, char *line)
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

static int	build_token(t_token **token, int type, int *k, char *content)
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

static int	build_token_word(int *table, char *line, int *k, t_token **token)
{
	int		start;
	int		end;
	char	*content;
	int		res;

	start = *k;
	if (!table)
		return (-1);
	while (*k < (int) ft_strlen(line) && table[*k] == 1)
		(*k)++;
	end = *k;
	content = ft_substr(line, start, end - start);
	if (!content)
		return (-3);
	res = build_token(token, T_WORD, k, content);
	if (res < 0)
		return (free(content), res);
	return (0);
}

static int	tokenize(int *table, char *line, t_token **token)
{
	int		k;
	int		res;

	k = 0;
	res = 0;
	while (line[k] && res == 0)
	{
		if (table[k] == 1)
			res = build_token_word(table, line, &k, token);
		else if (table[k] == 3)
			res = build_token(token, T_PIPE, &k, NULL);
		else if (table[k] == 5)
			res = build_token(token, T_RET_FROM, &k, NULL);
		else if (table[k] == 6)
			res = build_token(token, T_RET_TO, &k, NULL);
		else if (table[k] == 7)
			res = build_token(token, T_DLESS, &k, NULL);
		else if (table[k] == 8)
			res = build_token(token, T_DGREAT, &k, NULL);
		else
			k++;
	}
	return (res);
}

int	lexer(char *line, t_token **token)
{
	t_token	*end_token;
	int		*table;
	int		res;

	if (!line)
		return (-4);
	end_token = ft_tokennew(NULL, T_END);
	if (!end_token)
		return (-3);
	table = ft_calloc(ft_strlen(line), sizeof(int));
	if (!table)
		return (ft_tokendelone(end_token), -3);
	res = quote_sequence(table, line);
	if (res < 0)
		return (free(table), ft_tokendelone(end_token), res);
	operator_sequence(table, line);
	other_chars_sequence(table, line);
	res = tokenize(table, line, token);
	ft_tokenadd_back(token, end_token);
	return (free(table), res);
}
