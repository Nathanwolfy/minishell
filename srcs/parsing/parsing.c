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

#include "../../includes/common.h"

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

static int	ft_word_size_adapted(char *str, int (*f)(int))
{
	int	size;

	size = 0;
	while (str[size] && !((*f)(str[size])))
		size++;
	return (size);
}

static int	count_words_cmd(char *line, int to)
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

void	add_to_tree(char *line, int k, t_token **tree, int type)
{
	lexer1(line, k - 1, tree);
	ft_tokenadd_back(tree, ft_tokennew(NULL, type));
	if (type == T_PIPE || type == T_REDIRECT_IN || type == T_REDIRECT_OUT)
		lexer1(&line[k + 1], ft_strlen(&line[k + 1]), tree);
	else
		lexer1(&line[k + 2], ft_strlen(&line[k + 2]), tree);
}

int		check_for_operator(char *line, int k, t_token **tree)
{
	if (line[k] == '|') //what if last char
		return (add_to_tree(line, k, tree, T_PIPE), 1);
	else if (!ft_strncmp(&line[k], ">>", 2))
		return (add_to_tree(line, k, tree, T_REDIRECT_APP), 1);
	else if (!ft_strncmp(&line[k], "<<", 2))
		return (add_to_tree(line, k, tree, T_HERE_DOC), 1);
	else if (line[k] == '<')
		return (add_to_tree(line, k, tree, T_REDIRECT_IN), 1);
	else if (line[k] == '>')
		return (add_to_tree(line, k, tree, T_REDIRECT_OUT), 1);
	else
		return (0);
}

void	lexer1(char *line, int to, t_token **tree)
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
		else if (check_for_operator(line, k, tree) && !sq && !dq) //what if last char
			return ;
		k++;
	}
	if (sq || dq) //better handle
		printf("unclosed quote\n");
	else
	{
		k = -1;
		while (++k < count_words_cmd(line, to))
			ft_tokenadd_back(tree, ft_tokennew(ft_strdup("words"), T_WORD));
	}
}
