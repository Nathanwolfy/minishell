/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:05:42 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/16 15:43:29 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	handler_change_g_sig(int signum)
{
	g_sig = (sig_atomic_t)signum;
}

int	setup_interactive_mode(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = interactive_sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		return (ft_perror(), 1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		return (ft_perror(), 1);
	return (0);
}

int	setup_non_interactive_mode(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = non_interactive_sigquit_handler;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		return (ft_perror(), 1);
	sa.sa_handler = non_interactive_sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		return (ft_perror(), 1);
	return (0);
}
