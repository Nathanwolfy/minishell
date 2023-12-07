/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 11:51:42 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

int	ft_is_sq(int c)
{
	return (c == '\'');
}

int	ft_is_dq(int c)
{
	return (c == '\"');
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		free(split[i++]);
	free(split);
}

void	print_tree(t_token **tree)
{
	t_token	*l;

	if (!tree)
		return ;
	l = *tree;
	while (l)
	{
		printf("%s, type = %d\n", l->content, l->type);
		l = l->next;
	}
}

void	print_stash(t_stash **stash)
{
	t_stash	*l;
	int		p;

	if (!stash)
		return ;
	l = *stash;
	while (l)
	{
		printf("fdin_type : %d, filein_name %s\n", l->fdin_type, l->filein_name);
		printf("fdout_type : %d, fileout_name %s\n", l->fdout_type, l->fileout_name);
		p = 0;
		while (l->cmd && l->cmd[p])
			printf("%s\n", l->cmd[p++]);
		l = l->next;
	}
}
