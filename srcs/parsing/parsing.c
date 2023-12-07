/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:45:51 by nlederge          #+#    #+#             */
/*   Updated: 2023/12/07 11:46:35 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

static t_token	*skip_words(t_token *t)
{
	while (t && t->type == T_WORD)
		t = t->next;
	return (t);
}

static int	get_cmd_size(t_token **tree)
{
	t_token	*tl;
	int		k;

	k = 0;
	if (!tree)
		return (0);
	tl = *tree;
	while(tl && tl->type == T_WORD)
	{
		k++;
		tl = tl->next;
	}
	return (k);
}

static char	**create_cmd_tab(t_token **tree)
{
	char	**cmd;
	int		size;
	t_token	*tk;

	size = get_cmd_size(tree);
	cmd = ft_calloc(sizeof(char *), size + 1);
	if (!cmd)
		return (NULL);
	size = 0;
	tk = *tree;
	while (tk && tk->type == T_WORD)
	{
		cmd[size++] = ft_strdup(tk->content); //handle malloc error
		tk = tk->next;
	}
	cmd[size] = 0;
	return (cmd);
}

void	parser(t_stash **stash, t_token **tree)
{
	t_token	*t;
	char	**cmd;

	if (!tree)
		return ;
	t = *tree;
	while (t)
	{
		if (t->type == T_WORD)
		{
			cmd = create_cmd_tab(&t);
			ft_stashadd_back(stash, ft_stashnew(cmd));
			// create tab of strings for cmd, assign fdin fdout
			t = skip_words(t);
			// how to handle files instead of cmds
		}
		else
		{
			//how to go to next
			t = t->next;
		}
	}
}
