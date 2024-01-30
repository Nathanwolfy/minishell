/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/30 19:27:28 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	prompt(char *envp[])
{
	char	*line;
	int		running;
	t_token	*token;
	t_tree	*ast;

	running = 1;
	token = NULL;
	ast = NULL;
	while (running)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		running = lexer(line, &token); //display error message if needed
		if (!running)
		{
			ast = ast_builder(&token);
			//print_ast(ast, 0, 0);
			interpreter(&ast, envp);
		}
		if (!running && check_dless(ast) == 0)
			add_history(line);
		free(line);
		ft_tokenclear(&token);
		if (!running)
			ft_treeclear(&ast);
		running = 1;
	}
}
