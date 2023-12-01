/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:05 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/20 17:51:43 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*map;
	t_list	*new;
	void	*c;

	if (!lst || !f || !del)
		return (NULL);
	p = lst;
	map = NULL;
	while (p != NULL)
	{
		c = (*f)(p->content);
		new = ft_lstnew(c);
		if (!new)
		{
			del(c);
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, new);
		p = p->next;
	}
	return (map);
}
