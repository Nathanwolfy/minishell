/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:41:11 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/30 19:08:05 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ft_treedelone(t_tree *lst)
{
	if (!lst || lst == NOT_FOUND)
		return ;
	if (lst->content)
		free(lst->content);
	free(lst);
}

void	ft_treeclear(t_tree **lst)
{
	t_tree	*tmp_left;
	t_tree	*tmp_right;

	if (!lst || !(*lst) || (*lst) == NOT_FOUND)
		return ;
	tmp_left = (*lst)->left;
	tmp_right = (*lst)->right;
	ft_treedelone(*lst);
	lst = NULL;
	if (tmp_left)
		ft_treeclear(&tmp_left);
	if (tmp_right)
		ft_treeclear(&tmp_right);
}

t_tree	*ft_treenew(void *content, int type)
{
	t_tree	*l;

	l = ft_calloc(1, sizeof(t_tree));
	if (!l)
		return (NULL);
	l->content = content;
	l->type = type;
	l->left = NULL;
	l->right = NULL;
	l->parent = NULL;
	return (l);
}
