/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:41:11 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/18 17:37:59 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

void	ft_tokendelone(t_token *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_tokenclear(t_token **lst, void (*del)(void*))
{
	t_token	*tmp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_tokendelone(*lst, del);
		*lst = tmp;
	}
	lst = NULL;
}

t_token	*ft_tokennew(void *content, int type)
{
	t_token	*l;

	l = malloc(sizeof(t_token));
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
