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

#include "../includes/common.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		free(split[i++]);
	free(split);
}

void	print_tree(t_list **tree)
{
	t_list *l;

	if (!tree)
		return ;
	l = *tree;
	while (l)
	{
		printf("%s\n", (char *)l->content);
		l = l->next;
	}
}
