/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 09:05:42 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/19 16:51:26 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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

int	setup_here_doc_mode(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		return (ft_perror(), 1);
	return (0);
}

void	s_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
