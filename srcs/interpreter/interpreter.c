/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:26:04 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 15:12:23 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
Backus-Naur-Form (BNF) grammar:
	<all>        ::=  <newline>
	<pipeline>   ::=  <comp_cmd> { '|' <comp_cmd> }
	<comp_cmd> ::=  { ( <redirect> | <word> ) }
	<redirect>   ::=  ( '<' | '>' | '<<' | '>>' ) <word>
	<word>       ::=  ( any character except certain special characters + env var)
*/

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

char	*find_complete_cmd(t_tree **ast, t_tree *node)
{
	t_tree	*parent;
	char	*temp;
	char	*cmd;

	if (!ast || !node)
		return (NULL);
	parent = find_parent(ast, node, *ast);
	if (!parent)
		return (NULL);
	temp = ft_strjoin(node->content, " ");
	if (!temp)
		return (NULL);
	cmd = ft_strjoin(temp, (parent->right)->content);
	free(temp);
	if (!cmd)
		return (NULL);
	return (cmd);
}

void	exec_simple_cmd(t_tree **ast, t_tree *node)
{
	char	*cmd;
	char	**args;

	if (!node)
		return ;
	cmd = find_complete_cmd(ast, node);
	if (!cmd)
		return ;
	args = NULL; //check_get_cmd(cmd);
	if (!args) //handle errors
		return (free(cmd));
	
}

void	interpreter(t_tree **ast, t_tree *node)
{
	if (!ast || !node)
		return ;
	interpreter(ast, node->left);
	interpreter(ast, node->right);
	//execute simple command
}
