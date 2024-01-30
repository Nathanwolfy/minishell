/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/30 18:58:19 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		free(split[i++]);
	free(split);
}

/*void	print_tokens(t_token **tokens)
{
 	t_token	*t;

 	if (!tokens)
 		return ;
 	t = *tokens;
 	while(t)
 	{
 		printf("content = %s, type = %d\n", t->content, t->type);
 		t = t->next;
 	}
}*/

void	print_table(int *table, int len)
{
	int k;

	k = 0;
	while (k < len)
	{
		ft_putnbr_fd(table[k], STDERR_FILENO);
		ft_putstr_fd(" ", STDERR_FILENO);
		k++;
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}
