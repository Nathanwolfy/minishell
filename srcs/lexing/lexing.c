/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:53:32 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 15:19:55 by nlederge         ###   ########.fr       */
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

void	add_to_token(char *line, int k, t_token **token, int type)
{
	t_token	*new_token;

	lexer(line, k - 1, token);
	new_token = ft_tokennew(NULL, type);
	if (!new_token)
		return ; //handle malloc errors
	ft_tokenadd_back(token, new_token);
	if (type == T_PIPE || type == T_RET_TO || type == T_RET_FROM)
		lexer(&line[k + 1], ft_strlen(&line[k + 1]), token);
	else
		lexer(&line[k + 2], ft_strlen(&line[k + 2]), token);
}

void	add_words_to_token(char *line, int to, t_token **token)
{
	char	**words;
	char	*content;
	t_token	*new_token;
	int		l;

	words = ft_split_adapted(line, to);
	if (!words)
		return ; //handle malloc errors and detect difference from void
	l = 0;
	while (words[l])
	{
		content = ft_strdup(words[l++]);
		if (!content)
			return ; //handle malloc errors
		new_token = ft_tokennew(content, T_WORD);
		if (!new_token)
			return ; //handle malloc errors
		ft_tokenadd_back(token, new_token);
	}
	free_split(words);
	
}

int		check_for_operator(char *line, int k, t_token **token)
{
	if (line[k] == '|')
		return (add_to_token(line, k, token, T_PIPE), 1);
	else if (!ft_strncmp(&line[k], ">>", 2))
		return (add_to_token(line, k, token, T_DGREAT), 1);
	else if (!ft_strncmp(&line[k], "<<", 2))
		return (add_to_token(line, k, token, T_DLESS), 1);
	else if (line[k] == '<')
		return (add_to_token(line, k, token, T_RET_FROM), 1);
	else if (line[k] == '>')
		return (add_to_token(line, k, token, T_RET_TO), 1);
	else
		return (0);
}

void	lexer(char *line, int to, t_token **token)
{
	int	sq;
	int	dq;
	int	k;

	sq = 0;
	dq = 0;
	k = 0;
	while (line[k] && k < to)
	{
		if (line[k] == '\'' && !dq)
			sq = (1 - sq);
		else if (line[k] == '\"' && !sq)
			dq = (1 - dq);
		else if (!sq && !dq && check_for_operator(line, k, token))
			return ;
		k++;
	}
	if (sq || dq)
		return ; //handle unclosed quotes
	else
		add_words_to_token(line, to, token);
}
