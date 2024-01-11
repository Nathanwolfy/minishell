/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 17:51:05 by nlederge         ###   ########.fr       */
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
		lexer(line, &token);
		//ast = parser(&token);
		//interpreter(&ast, ast);
		if (check_dless(ast) == 0)
			add_history(line);
		free(line);
		ft_tokenclear(&token);
		ft_treeclear(&ast);
	}
}
