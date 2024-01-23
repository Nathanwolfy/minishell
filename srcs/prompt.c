/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/23 18:48:12 by nlederge         ###   ########.fr       */
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
		running = lexer(line, &token);
		if (!running)
		{
			ast = ast_builder(&token);
			//print_ast(ast, 0, 0);
			interpreter(&ast, envp);
		}
		if (!running && check_dless(ast) == 0)
			add_history(line);
		running = 1;
		free(line);
		ft_tokenclear(&token);
		ft_treeclear(&ast);
	}
}
