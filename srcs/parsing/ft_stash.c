/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:21:18 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 11:50:28 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

void	ft_stashdelone(t_stash *lst)
{
	if (!lst)
		return ;
	free_split(lst->cmd);
	free(lst);
}

void	ft_stashclear(t_stash **lst)
{
	t_stash	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_stashdelone(*lst);
		*lst = tmp;
	}
	lst = NULL;
}

t_stash	*ft_stashnew(char **content)
{
	t_stash	*l;

	l = ft_calloc(sizeof(t_stash), 1);
	if (!l)
		return (NULL);
	l->cmd = content;
	l->fdin_type = STDIN_FILENO; //better defs
	l->filein_name = NULL;
	l->fdout_type = STDOUT_FILENO; //better defs
	l->fileout_name = NULL;
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
