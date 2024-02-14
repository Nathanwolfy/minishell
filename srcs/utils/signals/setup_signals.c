/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:05:42 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/14 10:44:46 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	handler_change_g_sig(int signum)
{
	g_sig = (sig_atomic_t)signum;
	printf("%d\n", (int)g_sig);
}

int	setup_interactive_mode(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler_change_g_sig;
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
	sa.sa_handler = handler_change_g_sig;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		return (ft_perror(), 1);
	return (0);
}
