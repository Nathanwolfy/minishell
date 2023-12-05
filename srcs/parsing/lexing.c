/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
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

void	add_to_tree(char *line, int k, t_token **tree, int type)
{
	lexer(line, k - 1, tree);
	ft_tokenadd_back(tree, ft_tokennew(NULL, type)); //handle malloc errors
	if (type == T_PIPE || type == T_REDIRECT_IN || type == T_REDIRECT_OUT)
		lexer(&line[k + 1], ft_strlen(&line[k + 1]), tree);
	else
		lexer(&line[k + 2], ft_strlen(&line[k + 2]), tree);
}

void	add_words_to_tree(char *line, int to, t_token **tree)
{
	char	**words;
	int		l;

	words = ft_split_adapted(line, to);
	if (!words) //handle malloc errors and detect diffrence from void
		return ;
	l = 0;
	while (words[l]) //handle malloc errors
		ft_tokenadd_back(tree, ft_tokennew(ft_strdup(words[l++]), T_WORD));
	free_split(words);
	
}

int		check_for_operator(char *line, int k, t_token **tree)
{
	if (line[k] == '|')
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

void	lexer(char *line, int to, t_token **tree)
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
		else if (!sq && !dq && check_for_operator(line, k, tree)) //what if last char
			return ;
		k++;
	}
	if (sq || dq) //better handle
		printf("unclosed quote\n");
	else
		add_words_to_tree(line, to, tree);
}
