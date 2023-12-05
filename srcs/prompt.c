/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/01 15:27:15 by nlederge         ###   ########.fr       */
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

	running = 1;
	tree = NULL;
	while (running)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		lexer(line, ft_strlen(line) + 1, &tree); //add to history if no here doc
		print_tree(&tree);
		add_history(line);
		ft_tokenclear(&tree, &free);
		tree = NULL;
		free(line);
	}
}
