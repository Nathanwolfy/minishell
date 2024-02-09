/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:40:04 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:42:17 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
char	**replace_shlvl(char *copied_envp[]);
char	**increment_shlvl(char *copied_envp[]);
char	**add_shlvl(char *copied_envp[]);
int		count_split(char *old_envp[]);

int	check_valid_shlvl_value(char **copied_envp)
{
	int		i;
	char	*shlvl_value;

	i = get_env_index("SHLVL", 5, copied_envp);
	if (i < 0)
		return (1);
	shlvl_value = copied_envp[i] + 6;
	if (!*shlvl_value)
		return (2);
	i = 0;
	while (shlvl_value[i])
	{
		if (!ft_isdigit(shlvl_value[i]))
			return (2);
		i++;
	}
	if (!shlvl_value[i])
		return (0);
	return (1);
}

char	**add_pwd(char *copied_envp[])
{
	char	**new_envp;
	char	*pwd_key;
	char	pwd_value[PATH_MAX];
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
	pwd_key = ft_strdup("PWD=");
	if (!pwd_key)
		return (free_split(new_envp), NULL);
	new_envp[i] = ft_strjoin(pwd_key, getcwd(pwd_value, (size_t) PATH_MAX));
	free(pwd_key);
	if (!new_envp[i++])
		return (free_split(new_envp), NULL);
	new_envp[i] = NULL;
	return (new_envp);
}

char	**replace_pwd(char *copied_envp[])
{
	int		i;
	char	pwd_value[PATH_MAX];
	char	*pwd_key;
	char	*new_pwd;

	i = get_env_index("PWD", 3, copied_envp);
	pwd_key = ft_strdup("PWD=");
	if (!pwd_key)
		return (free_split(copied_envp), NULL);
	new_pwd = ft_strjoin(pwd_key, getcwd(pwd_value, (size_t) PATH_MAX));
	free(pwd_key);
	if (!new_pwd)
		return (free_split(copied_envp), NULL);
	free(copied_envp[i]);
	copied_envp[i] = new_pwd;
	return (copied_envp);
}

char	**check_mandatory_envp(char *copied_envp[])
{
	char	**new_envp;

	if (check_valid_shlvl_value(copied_envp) == 1)
	{
		new_envp = add_shlvl(copied_envp);
		free_split(copied_envp);
	}
	else if (check_valid_shlvl_value(copied_envp) == 2)
		new_envp = replace_shlvl(copied_envp);
	else
		new_envp = increment_shlvl(copied_envp);
	if (!new_envp)
		return (NULL);
	copied_envp = new_envp;
	if (get_env_index("PWD", 3, copied_envp) < 0)
	{
		new_envp = add_pwd(copied_envp);
		free_split(copied_envp);
	}
	else
		new_envp = replace_pwd(copied_envp);
	if (!new_envp)
		return (NULL);
	return (new_envp);
}
