/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:04:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/16 18:11:23 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	**create_new_envp(char **env)
{
	int		ct;
	char	**new;

	ct = get_double_arr_len(env);
	new = ft_calloc(ct, sizeof(char *));
	if (!new && ft_perror())
		return (NULL);
	return (new);
}

static int	dup_envp(char ***envp, int index_to_skip)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = create_new_envp(*envp);
	if (!new)
		return (1);
	while ((*envp)[j])
	{
		if (j == index_to_skip)
		{
			j++;
			continue ;
		}
		new[i] = ft_strdup((*envp)[j]);
		if (!new && ft_perror())
			return (free_split(new), 1);
		i++;
		j++;
	}
	free_split(*envp);
	*envp = new;
	return (0);
}

static int	remove_var(char *var, char ***envp)
{
	int		index_to_skip;

	index_to_skip = get_env_index(var, ft_strlen(var), *envp);
	if (index_to_skip == -1)
		return (0);
	return (dup_envp(envp, index_to_skip));
}

int	builtin_unset(char **cmd, char ***envp)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!cmd || !*cmd || !envp || !*envp)
		return (exit_status);
	while (cmd[i])
	{
		if (remove_var(cmd[i], envp))
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
