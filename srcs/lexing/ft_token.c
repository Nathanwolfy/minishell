/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:41:11 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/30 19:06:24 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ft_tokendelone(t_token *lst)
{
	if (!lst)
		return ;
	if (lst->content)
		free(lst->content);
	lst->content = NULL;
	free(lst);
}

void	ft_tokenclear(t_token **lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_tokendelone(*lst);
		*lst = tmp;
	}
	lst = NULL;
}

t_token	*ft_tokennew(void *content, int type)
{
	t_token	*l;

	l = ft_calloc(1, sizeof(t_token));
	if (!l)
		return (NULL);
	l->content = content;
	l->type = type;
	l->next = NULL;
	return (l);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_tokenlast(lst->next));
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_tokenlast(*lst);
	last->next = new;
}
