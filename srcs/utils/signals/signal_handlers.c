/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:53:03 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/14 11:00:36 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	signal_redisplay(void)
{
	rl_replace_line("", 1);
	rl_redisplay();
	rl_on_nl();
}
