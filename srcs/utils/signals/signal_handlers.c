/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:53:03 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/14 11:47:27 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	signal_redisplay(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "\nminishell: ", 12);
	g_sig = 0;
}

void	interactive_sigint_handler(int signum)
{
	(void)signum;
	signal_redisplay();
}

void	non_interactive_sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	non_interactive_sigquit_handler(int signum)
{
	(void)signum;
	g_sig = signum;
	write(1, "Quit\n", 5);
}
