/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:02:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 18:41:57 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(void)
{
	/*t_tree	*pipe;
	pipe = ft_treenew(ft_strdup("pipe"), 0);
	t_tree	*cmd_ls;
	cmd_ls = ft_treenew(ft_strdup("ls"), 0);
	t_tree	*cmd_ls_arg1;
	cmd_ls_arg1 = ft_treenew(ft_strdup("-la"), 0);
	t_tree	*cmd_ls_arg2;
	cmd_ls_arg2 = ft_treenew(ft_strdup("minishell"), 0);
	t_tree	*cmd_ls_ret_to;
	cmd_ls_ret_to = ft_treenew(ft_strdup(">"), 0);
	t_tree	*cmd_ls_ret_to_filename;
	cmd_ls_ret_to_filename = ft_treenew(ft_strdup("outfile"), 0);
	t_tree	*cmd_grep;
	cmd_grep = ft_treenew(ft_strdup("grep"), 0);
	t_tree	*cmd_grep_arg;
	cmd_grep_arg = ft_treenew(ft_strdup("srcs"), 0);

	pipe->left = cmd_ls;
	cmd_ls->left = cmd_ls_arg1;
	cmd_ls_arg1->left = cmd_ls_arg2;
	cmd_ls->right = cmd_ls_ret_to;
	cmd_ls_ret_to->left = cmd_ls_ret_to_filename;
	pipe->right = cmd_grep;
	cmd_grep->left = cmd_grep_arg;
	ft_putendl_fd("Test printing AST for command : \"ls -la minishell > outfile | grep srcs\"", 1);
	print_ast(pipe, 0, 0);
	ft_treeclear(&pipe);
	*/
	prompt();
	return (0);
}
