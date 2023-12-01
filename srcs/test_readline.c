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

#include "../includes/minishell.h"

void	prompt(void)
{
	char	*line;
	int		running;
	//char	*paths;

	//line = readline(PROMPT);
	//printf("line = %s\n", line);
	//paths = getenv("PATH");
	//printf("paths = %s\n", paths);
	//free(line);
	running = 10;
	while (running--)
	{
		line = readline(PROMPT);
		add_history(line);
		if (running == 5)
			rl_clear_history();
		printf("line = %s\n", line);
		free(line);
	}

}
