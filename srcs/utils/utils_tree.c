/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:41:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/12 12:49:46 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	print_tree_node(t_tree *node, int indent_ct, char side)
{
	int	i;

	if (!node || node == NOT_FOUND)
		return ;
	i = -1;
	while (++i < indent_ct)
		ft_putchar_fd('\t', 1);
	if (side == 'l')
		ft_putstr_fd("left: ", 1);
	else if (side == 'r')
		ft_putstr_fd("right: ", 1);
	ft_putstr_fd("type: ", 1);
	ft_putnbr_fd(node->type, 1);
	ft_putstr_fd(" - content: ", 1);
	ft_putendl_fd(node->content, 1);
}

void	print_ast(t_tree *tree, int indent_ct, char side)
{
	if (!tree || tree == NOT_FOUND)
		return ;
	print_tree_node(tree, indent_ct, side);
	print_ast(tree->left, indent_ct + 1, 'l');
	print_ast(tree->right, indent_ct + 1, 'r');
}

int	check_dless(t_tree *tree)
{
	if (!tree || tree == NOT_FOUND)
		return (0);
	if (tree->type == R_IO_FILE_DLESS)
		return (1);
	return (check_dless(tree->left) + check_dless(tree->right));
}
