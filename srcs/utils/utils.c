/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2023/11/16 16:56:08 by nlederge         ###   ########.fr       */
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
