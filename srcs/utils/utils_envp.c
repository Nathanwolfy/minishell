/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:27 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/07 01:10:11 by nlederge         ###   ########.fr       */
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

/*
Check for mandatory environment variables :
- valid SHLVL value and increment it
- reset PWD whatever the value
*/

char	**check_shlvl(char *copied_envp[]) //keep track of memory but almost done
{
	char	*shlvl;
	int		shlvl_value;
	char	*new_shlvl;
	char	**new_envp;
	int		index;

	index = get_env_index("SHLVL", 5, copied_envp); //ask the GOAT Ellio about this
	if (index < 0)
	{
		new_shlvl = ft_strdup("SHLVL=1");
		if (!new_shlvl)
			return (NULL);
		new_envp = add_envp(copied_envp, new_shlvl);
		return (new_envp);
	}
	shlvl_value = check_shlvl_value(copied_envp[index]);
	if (shlvl_value < 0)
		return (NULL);
	shlvl = ft_itoa(shlvl_value + 1);
	if (!shlvl)
		return (NULL);
	new_shlvl = ft_strjoin("SHLVL=", shlvl);
	if (!new_shlvl)
		return (free(shlvl), NULL);
	return (free(shlvl), add_envp(copied_envp, new_shlvl));
}

char	**check_mandatory_envp(char *copied_envp[])
{
	char	**new_envp;

	new_envp = check_shlvl(copied_envp);
	if (!new_envp)
		return (free_split(copied_envp), NULL);
	copied_envp = new_envp;
	new_envp = check_pwd(copied_envp);
	if (!new_envp)
		return (free_split(copied_envp), NULL);
	return (copied_envp);
}