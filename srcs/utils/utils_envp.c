/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:27 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/31 13:24:51 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	count_split(char *old_envp[])
{
	int	k;

	if (!old_envp)
		return (0);
	k = 0;
	while (old_envp[k])
		k++;
	return (k);
}

char	**copy_envp(char *old_envp[])
{
	char	**envp;
	int		ct;
	int		l;

	ct = count_split(old_envp);
	envp = ft_calloc(ct + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	l = 0;
	while (l < ct)
	{
		envp[l] = ft_strdup(old_envp[l]);
		if (!envp[l])
			return (free_split(envp), NULL);
		l++;
	}
	envp[l] = NULL;
	return (envp);
}

char	**create_envp(void) //how to increase SHELL level ?
{
	char	**envp;
	char	cwd[1000]; //better way to do that ?

	envp = ft_calloc(4, sizeof(char *));
	if (!envp)
		return (NULL);
	envp[0] = ft_strdup(getcwd(cwd, 1000));
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=/usr/bin/env"); //or "_=./minishell"
	envp[3] = NULL;
	return (envp);
}