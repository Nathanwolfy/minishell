/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:53:03 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/19 17:08:20 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	signal_redisplay(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "\nminishell: ", 12);
}

void	interactive_sigint_handler(int signum)
{
	(void)signum;
	signal_redisplay();
	g_sig = signum;
}

void	non_interactive_sigint_handler(int signum)
{
	g_sig = signum;
	write(1, "\n", 1);
}

void	non_interactive_sigquit_handler(int signum)
{
	g_sig = signum;
	write(1, "Quit\n", 5);
}

void	handle_sigquit(int *exit_status, t_malloc_data *data)
{
	if (data->flag_quit == 1 && *exit_status == 131)
	{
		ft_putendl_fd("Quit", STDOUT_FILENO);
		data->flag_quit = 0;
	}
	g_sig = 0;
}
