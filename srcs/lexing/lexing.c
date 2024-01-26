/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:53:32 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/26 15:41:43 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
Examples of lexing :
ls -l | grep srcs
T_WORD T_WORD T_PIPE T_WORD T_WORD
< cat | grep this >> file1
T_RET_FROM T_WORD T_PIPE T_WORD T_WORD T_WORD T_DGREAT T_WORD
cat infile | grep "< ouch $TEST" > outfile
T_WORD T_WORD T_PIPE T_WORD T_WORD T_RET_TO T_WORD
*/

int	add_operator_to_token(char *line, int k, t_token **token, int type)
{
	t_token	*new_token;
	int		res;

	res = lexer_rec(line, k - 1, token);
	if (res < 0)
		return (res);
	new_token = ft_tokennew(NULL, type, 0);
	if (!new_token)
		return (-1);
	ft_tokenadd_back(token, new_token);
	if (type == T_PIPE || type == T_RET_TO || type == T_RET_FROM)
		return (lexer_rec(&line[k + 1], ft_strlen(&line[k + 1]), token));
	else
		return (lexer_rec(&line[k + 2], ft_strlen(&line[k + 2]), token));
}

int		check_for_operator(char *line, int k, t_token **token)
{
	int	res;

	res = 0;
	if (line[k] == '|')
		res = add_operator_to_token(line, k, token, T_PIPE);
	else if (!ft_strncmp(&line[k], ">>", 2))
		res = add_operator_to_token(line, k, token, T_DGREAT);
	else if (!ft_strncmp(&line[k], "<<", 2))
		res = add_operator_to_token(line, k, token, T_DLESS);
	else if (line[k] == '<')
		res = add_operator_to_token(line, k, token, T_RET_FROM);
	else if (line[k] == '>')
		res = add_operator_to_token(line, k, token, T_RET_TO);
	else
		return (1);
	return (res);
}

int	add_words_to_token(char *line, int to, t_token **token)
{
	char	**words;
	char	*content;
	t_token	*new_token;
	int		l;

	words = ft_split_adapted(line, to);
	if (!words)
		return (ft_putstr_fd("testing NULL return from split", 2), 0); //handle malloc errors and detect difference from void
	l = 0;
	while (words[l])
	{
		content = ft_strdup(words[l++]);
		if (!content)
			return (-1);
		new_token = ft_tokennew(content, T_WORD, 1);
		if (!new_token)
			return (-1);
		ft_tokenadd_back(token, new_token);
	}
	free_split(words);
	return (0);
}

int	lexer_rec(char *line, int to, t_token **token)
{
	int	sq;
	int	dq;
	int	k;
	int	res;

	sq = 0;
	dq = 0;
	k = 0;
	while (line[k] && k < to)
	{
		if (line[k] == '\'' && !dq)
			sq = (1 - sq);
		else if (line[k] == '\"' && !sq)
			dq = (1 - dq);
		else if (!sq && !dq)
		{
			res = check_for_operator(line, k, token);
			if (res != 1)
				return (res);
		}
		k++;
	}
	if (sq || dq)
		return (unclosed_quotes_code(sq, dq));
	return (add_words_to_token(line, to, token));
}

int	lexer(char *line, t_token **token)
{
	t_token	*end_token;
	int		res;

	end_token = ft_tokennew(NULL, T_END, 0);
	if (!end_token)
		return (print_error_lexing_code(-1));
	res = lexer_rec(line, ft_strlen(line) + 1, token);
	ft_tokenadd_back(token, end_token);
	if (res < 0)
		return (print_error_lexing_code(res));
	res = check_token_quotes(token);
	if (res < 0)
		return (print_error_lexing_code(res));
	return (res);
}
