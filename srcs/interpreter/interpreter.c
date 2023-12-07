/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:26:04 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 15:35:43 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

t_tree	*find_parent(t_tree **ast, t_tree *needle, t_tree *curr)
{
	t_tree	*t;

	if (!ast || !needle || !curr)
		return (NULL);
	if (curr->left == needle)
		return (curr);
	t = find_parent(ast, needle, curr->left);
	if (t)
		return (t);
	t = find_parent(ast, needle, curr->right);
	if (t)
		return (t);
	return (NULL);
}

char	**find_args(t_tree **ast, t_tree *node)
{
	t_tree	*parent;
	char	**args;
	char	*temp1;
	char	*temp2;

	if (!ast || !node)
		return (NULL);
	parent = find_parent(ast, node, *ast);
	if (!parent)
		return (NULL);
	temp1 = ft_strjoin(node->content, ' ');
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, (parent->right)->content);
	free(temp1);
	if (!temp2)
		return (NULL);
	args = ft_split_adapted(temp2, ft_strlen(temp2));
	free(temp2);
	if (!args)
		return (NULL);
	return (args);
}

void	exec_simple_cmd(t_tree **ast, t_tree *node)
{
	char	**args;

	if (!node)
		return ;
	args = find_args(ast, node);
	if (!args)
		return ;
	
}

void	interpreter(t_tree **ast, t_tree *node)
{
	if (!ast || !node)
		return ;
	interpreter(ast, node->left);
	interpreter(ast, node->right);
	//execute simple command
}
