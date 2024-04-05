/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/20 16:57:22 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

sig_atomic_t	g_sig = 0;

static void	free_lines(char *line, char *old_line, int code, int *running)
{
	if (line && (code == 1 || code == 3))
	{
		free(line);
		line = NULL;
	}
	if (old_line && (code == 2 || code == 3))
	{
		free(old_line);
		old_line = NULL;
	}
	if (running)
		*running = 1;
}

static char	*initialize_line(char ***envp, char **old_line, int *exit_status, \
t_malloc_data *data)
{
	char	*line;

	handle_sigquit(exit_status, data);
	if (setup_interactive_mode())
		return (NULL);
	*old_line = readline(PROMPT);
	if (g_sig == SIGINT)
		*exit_status = 130;
	if (!*old_line)
	{
		*exit_status = 0;
		free_split(*envp);
		return (NULL);
	}
	if (setup_non_interactive_mode())
		return (NULL);
	line = format_cmd_line(*old_line, *envp, *exit_status);
	if (line == (char *)-1)
		return ((char *)-1);
	else if (!line)
		return (NULL);
	return (line);
}

static void	initialize_ast_and_execute(t_token **token, t_tree **ast, \
t_malloc_data *data, int *exit_status)
{
	int	res;

	*ast = ast_builder(token);
	ft_tokenclear(token);
	if (!ast || !*ast)
	{
		*exit_status = 1;
		return ;
	}
	data->ast = ast;
	if (setup_here_doc_mode())
		return ;
	res = here_doc_sequence(*ast);
	if (!res)
	{
		if (setup_non_interactive_mode())
			return ;
		*exit_status = interpreter(data, ast);
		data->flag_quit = 1;
	}
	else
		*exit_status = res;
	ft_treeclear(ast);
}

static void	set_malloc_data(t_malloc_data *data, char *old_line, char ***envp)
{
	data->old_line = old_line;
	data->envp = envp;
}

void	prompt(int running, t_token *token, t_tree *ast, char **envp[])
{
	char			*line;
	char			*old_line;
	int				exit_status;
	t_malloc_data	data;

	exit_status = 0;
	data.flag_quit = 0;
	while (running)
	{
		line = initialize_line(envp, &old_line, &exit_status, &data);
		if (line == (char *)-1)
			continue ;
		else if (!line)
			return ;
		running = lexer(line, &token);
		free_lines(line, old_line, 1, NULL);
		set_malloc_data(&data, old_line, envp);
		if (print_error_lexer(running, &exit_status) < 0)
			ft_tokenclear(&token);
		else
			initialize_ast_and_execute(&token, &ast, &data, &exit_status);
		if (old_line)
			add_history(old_line);
		free_lines(line, old_line, 2, &running);
	}
}
