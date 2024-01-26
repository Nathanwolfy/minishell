/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:41:11 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/26 15:40:23 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ft_tokendelone(t_token *lst)
{
	if (!lst)
		return ;
	free(lst->content);
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

t_token	*ft_tokennew(void *content, int type, int handle_expansion)
{
	t_token	*l;

	l = ft_calloc(sizeof(t_token), 1);
	if (!l)
		return (NULL);
	l->content = content;
	l->type = type;
	l->handle_expansion = handle_expansion;
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
