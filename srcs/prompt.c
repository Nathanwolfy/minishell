/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
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

	running = 1;
	while (running)
	{
		line = readline(PROMPT);
		//parsing of line
		lexer1(line, ft_strlen(line) + 1);
		//add to history if no here doc
		add_history(line);
		free(line);
	}
}
