/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:27 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:42:23 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	count_split(char *old_envp[])
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

/*
Check for mandatory environment variables :
- valid SHLVL value and increment it
- reset PWD whatever the value
*/

char	**add_shlvl(char *copied_envp[])
{
	char	**new_envp;
	char	*shlvl_key;
	int		i;

	new_envp = ft_calloc(count_split(copied_envp) + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (copied_envp[i])
	{
		new_envp[i] = ft_strdup(copied_envp[i]);
		if (!new_envp[i])
			return (free_split(new_envp), NULL);
		i++;
	}
	shlvl_key = ft_strdup("SHLVL=");
	if (!shlvl_key)
		return (free_split(new_envp), NULL);
	new_envp[i] = ft_strjoin(shlvl_key, "1");
	free(shlvl_key);
	if (!new_envp[i++])
		return (free_split(new_envp), NULL);
	new_envp[i] = NULL;
	return (new_envp);
}

char	**increment_shlvl(char *copied_envp[])
{
	int		i;
	char	*shlvl_value;
	char	*new_shlvl_value;
	char	*new_shlvl;

	i = get_env_index("SHLVL", 5, copied_envp);
	shlvl_value = copied_envp[i] + 6;
	if (!*shlvl_value)
		return (free_split(copied_envp), NULL);
	new_shlvl_value = ft_itoa(ft_atoi(shlvl_value) + 1);
	if (!new_shlvl_value)
		return (free_split(copied_envp), NULL);
	new_shlvl = ft_strjoin("SHLVL=", new_shlvl_value);
	free(new_shlvl_value);
	if (!new_shlvl)
		return (free_split(copied_envp), NULL);
	free(copied_envp[i]);
	copied_envp[i] = new_shlvl;
	return (copied_envp);
}

char	**replace_shlvl(char *copied_envp[])
{
	int		i;
	char	*new_shlvl;

	i = get_env_index("SHLVL", 5, copied_envp);
	new_shlvl = ft_strdup("SHLVL=1");
	if (!new_shlvl)
		return (free_split(copied_envp), NULL);
	free(copied_envp[i]);
	copied_envp[i] = new_shlvl;
	return (copied_envp);
}
