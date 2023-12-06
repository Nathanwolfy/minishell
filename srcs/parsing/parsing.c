/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:45:51 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/06 17:37:18 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

void	parser(t_stash **stash, t_token **tree)
{
	t_token	*t;
	char	**cmd;

	if (!tree)
		return (NULL);
	t = *tree;
	while (t)
	{
		if (t->type == T_WORD)
		{
			cmd = create_cmd_tab();
			ft_stashadd_back(stash, ft_stashnew(cmd));
			// create tab of strings for cmd, assign fdin fdout
			// skip to next
		}
		else
		{
			//how to go to next
		}
	}
}
