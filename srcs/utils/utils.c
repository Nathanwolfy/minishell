/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 15:19:08 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

int	ft_is_sq(int c)
{
	return (c == '\'');
}

int	ft_is_dq(int c)
{
	return (c == '\"');
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		free(split[i++]);
	free(split);
}

void	print_tree_node(t_tree *node, int indent_ct)
{
	int	i;

	if (!node)
		return ;
	i = -1;
	while (++i > indent_ct)
		ft_putchar_fd('\t', 1);
	ft_putstr_fd("type: ", 1);
	ft_putnbr_fd(node->type, 1);
	ft_putstr_fd(" - content: ", 1);
	ft_putendl_fd(node->content, 1);
}

void	print_ast(t_tree *tree, int indent_ct)
{
	if (!tree)
		return ;
	print_tree_node(tree, indent_ct);
	print_ast(tree->left, indent_ct + 1);
	print_ast(tree->right, indent_ct + 1);
}
