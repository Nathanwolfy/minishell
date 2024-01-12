/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:05 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	exec_cmd(char *cmd)
{
	printf("%s\n", cmd);
}

void	prompt(void)
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
		print_tokens(&token);
		if (!running)
		{
			ast = ast_builder(&token);
		}
		if (!running || check_dless(ast) == 0)
			add_history(line);
		running = 1;
		print_tokens(&token);
		//print_ast(ast, 0, 0);
		free(line);
		ft_tokenclear(&token);
		ft_treeclear(&ast);
	}
}
