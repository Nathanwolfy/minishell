/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:58:01 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/19 13:25:15 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*get_word_content(int len, int *k, int *table, char *line)
{
	int		line_len;
	char	*content;
	int		i;

	i = 0;
	line_len = (int)ft_strlen(line);
	content = ft_calloc(len + 1, sizeof(char));
	if (!content)
		return (ft_perror(), NULL);
	while (*k < line_len && (table[*k] == 1 || table[*k] == -1))
	{
		if (table[*k] == 1)
			content[i++] = line[(*k)++];
		else
			*k += 1;
	}
	return (content);
}

static int	get_content_len(int *table, char *line, int k)
{
	int		len;
	int		line_len;

	len = 0;
	line_len = (int)ft_strlen(line);
	while (k < line_len && (table[k] == 1 || table[k] == -1))
	{
		if (table[k] == 1)
			len++;
		k++;
	}
	return (len);
}

static int	build_token_word(int *table, char *line, int *k, t_token **token)
{
	char	*content;
	int		content_len;
	int		res;

	content_len = get_content_len(table, line, *k);
	content = get_word_content(content_len, k, table, line);
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
	operator_sequence(table, line);
	res = quote_sequence(table, line);
	if (res < 0)
		return (free(table), ft_tokendelone(end_token), res);
	other_chars_sequence(table, line);
	res = tokenize(table, line, token);
	ft_tokenadd_back(token, end_token);
	return (free(table), res);
}
