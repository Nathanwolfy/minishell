/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:27:14 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 14:21:03 by nlederge         ###   ########.fr       */
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
	t_token	*token;

	running = 1;
	token = NULL;
	while (running)
	{
		line = readline(PROMPT);
		if (!line)
			return ;
		lexer(line, ft_strlen(line) + 1, &token); //add to history if no here doc
		add_history(line);
		ft_tokenclear(&token);
		token = NULL;
		free(line);
	}
}
