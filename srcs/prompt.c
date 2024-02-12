/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/11 17:07:21 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	free_lines(char *line, char *old_line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (old_line)
	{
		free(old_line);
		old_line = NULL;
	}
}

void	prompt(t_token *token, t_tree *ast, char **envp[])
{
	char	*line;
	char	*old_line;
	int		running;
	int		exit_status;

	running = 1;
	exit_status = 0;
	while (running)
	{
		old_line = readline(PROMPT);
		line = format_cmd_line(old_line, *envp, exit_status);
		if (line == (char *)-1)
		{
			exit_status = 0;
			continue ;
		}
		running = lexer(line, &token);
		if (print_error_lexer(running, &exit_status) < 0)
			ft_tokenclear(&token);
		else //update exit status in case of errors
		{
			ast = ast_builder(&token); //catch error code from ast
			print_ast(ast, 0, 'l');
			ft_tokenclear(&token);
			if (!here_doc_sequence(ast))
				exit_status = interpreter(&ast, envp);	
			else
				exit_status = 1;
			ft_treeclear(&ast);
		}
		if (old_line)
			add_history(old_line);
		free_lines(line, old_line);
		running = 1;
	}
}
