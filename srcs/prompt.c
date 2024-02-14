/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/14 16:01:56 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

sig_atomic_t	g_sig = 0;

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

static char	*initialize_line(char **envp, char **old_line, int *exit_status)
{
	char	*line;

	if (setup_interactive_mode())
		return (NULL);
	*old_line = readline(PROMPT);
	if (!*old_line)
	{
		*exit_status = 0;
		return (NULL);
	}
	if (setup_non_interactive_mode())
		return (NULL);
	line = format_cmd_line(*old_line, envp, *exit_status);
	if (line == (char *)-1)
	{
		*exit_status = 0;
		return ((char *)-1);
	}
	else if (!line)
		return (NULL);
	return (line);
}

static void	initialize_ast_and_execute(t_token **token, t_tree **ast, char ***envp,\
int *exit_status)
{
	*ast = ast_builder(token); // error
	print_ast(*ast, 0, '\0');
	ft_tokenclear(token);
	if (!here_doc_sequence(*ast))
		*exit_status = interpreter(ast, envp);
	else
		*exit_status = 1;
	ft_treeclear(ast);
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
		line = initialize_line(*envp, &old_line, &exit_status);
		if (line == (char *)-1)
			continue ;
		else if (!line)
			return ;
		running = lexer(line, &token);
		if (print_error_lexer(running, &exit_status) < 0)
			ft_tokenclear(&token);
		else //update exit status in case of errors
			initialize_ast_and_execute(&token, &ast, envp, &exit_status);
		if (old_line)
			add_history(old_line);
		free_lines(line, old_line);
		running = 1;
	}
}
