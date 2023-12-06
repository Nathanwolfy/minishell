/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:21:18 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/06 17:31:34 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

void	ft_stashdelone(t_stash *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->cmd);
	free(lst);
}

void	ft_stashclear(t_stash **lst, void (*del)(void*))
{
	t_stash	*tmp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_stashdelone(*lst, del);
		*lst = tmp;
	}
	lst = NULL;
}

t_stash	*ft_stashnew(void **content)
{
	t_stash	*l;

	l = malloc(sizeof(t_stash));
	if (!l)
		return (NULL);
	l->cmd = content;
	l->fdin = STDIN_FILENO;
	l->fdout = STDOUT_FILENO;
	l->next = NULL;
	return (l);
}

t_stash	*ft_stashlast(t_stash *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_stashlast(lst->next));
}

void	ft_stashadd_back(t_stash **lst, t_stash *new)
{
	t_stash	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_stashlast(*lst);
	last->next = new;
}
