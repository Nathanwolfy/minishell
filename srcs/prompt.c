/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/02 11:24:08 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	prompt(t_token *token, t_tree *ast, char *envp[])
{
	char	*line;
	int		running;

	running = 1;
	while (running)
	{
		line = readline(PROMPT);
		running = lexer(line, &token);
		if (print_error_lexer(running) < 0)
			ft_tokenclear(&token);
		else
		{
			ast = ast_builder(&token); //catch error code from ast
			interpreter(&ast, envp); //catch error code from interpreter
			ft_tokenclear(&token);
			ft_treeclear(&ast);
		}
		add_history(line);
		free(line);
		running = 1;
	}
}
