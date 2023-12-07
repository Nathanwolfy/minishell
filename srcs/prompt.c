/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 11:43:26 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/common.h"

void	exec_cmd(char *cmd)
{
	printf("%s\n", cmd);
}

void	prompt(void)
{
	char	*line;
	int		running;
	t_token	*tree;
	t_stash	*stash;

	running = 1;
	tree = NULL;
	stash = NULL;
	while (running)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		lexer(line, ft_strlen(line) + 1, &tree); //add to history if no here doc
		parser(&stash, &tree);
		print_stash(&stash);
		add_history(line);
		ft_tokenclear(&tree, &free);
		ft_stashclear(&stash);
		stash = NULL;
		tree = NULL;
		free(line);
	}
}
