/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:27 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/23 18:48:25 by nlederge         ###   ########.fr       */
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