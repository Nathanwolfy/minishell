/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:53:32 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/01 17:53:33 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/common.h"

/*
Possibilities : commands, options, ', ", $ (?), |, <, <<, >, >>

Tkens yet to be defined

Examples of parsing :
ls -l | grep srcs
cmd opt pipe cmd opt
< cat | grep this >> file1
redir cmd pipe cmd opt redir file (?)
cat infile | grep "< ouch $TEST" > outfile
cmd opt pipe cmd opt (ENV?) redir file (?)
*/

static int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

static int	ft_is_sq(int c)
{
	return (c == '\'');
}

static int	ft_is_dq(int c)
{
	return (c == '\"');
}

static int	ft_word_size_adapted(char *str, int (*f)(int))
{
	int	size;

	size = 0;
	while (str[size] && !((*f)(str[size])))
		size++;
	return (size);
}

int	count_words_cmd(char *line, int to)
{
	int	ct;
	int	size;
	int	j;

	ct = 0;
	j = 0;
	while (line[j] && j < to)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		if (line[j] == '\'')
			size = ft_word_size_adapted(&line[j + 1], &ft_is_sq) + 2;
		else if (line[j] == '\"')
			size = ft_word_size_adapted(&line[j + 1], &ft_is_dq) + 2;
		else
			size = ft_word_size_adapted(&line[j], &ft_isspace);
		j += size;
		if (size != 0)
			ct++;
		else
			return (ct);
	}
	return (ct);
}

void	lexer1(char *line, int to, t_list **tree)
{
	int	sq;
	int	dq;
	int	k;

	sq = 0;
	dq = 0;
	k = 0;
	k = 0;
	while (line[k] && k < to)
	{
		if (line[k] == '\'' && !dq)
			sq = (1 - sq);
		else if (line[k] == '\"' && !sq)
			dq = (1 - dq);
		else if (line[k] == '|' && !sq && !dq) //what if last char
		{
			lexer1(line, k - 1, tree);
			//printf("pipe\n");
			ft_lstadd_back(tree, ft_lstnew(ft_strdup("pipe")));
			lexer1(&line[k + 1], ft_strlen(&line[k + 1]), tree);
			return ;
		}
		else if (line[k] == '<' && !sq && !dq)
		{
			lexer1(line, k - 1, tree);
			//printf("<\n");
			ft_lstadd_back(tree, ft_lstnew(ft_strdup("<")));
			lexer1(&line[k + 1], ft_strlen(&line[k + 1]), tree);
			return ;
		}
		else if (line[k] == '>' && !sq && !dq)
		{
			lexer1(line, k - 1, tree);
			//printf(">\n");
			ft_lstadd_back(tree, ft_lstnew(ft_strdup(">")));
			lexer1(&line[k + 1], ft_strlen(&line[k + 1]), tree);
			return ;
		}
		k++;
	}
	/*if (sq)
		printf("unclosed single quote");
	if (dq)
		printf("unclosed double quote");*/
	//handle unclosed quotes
	//count words
	k = 0;
	while (k < count_words_cmd(line, to))
	{
		//printf("words\n");
		ft_lstadd_back(tree, ft_lstnew(ft_strdup("words")));
		k++;
	}
}
