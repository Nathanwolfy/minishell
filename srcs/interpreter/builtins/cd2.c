/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:11:09 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/09 14:11:27 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	replace_old_pwd(char ***envp, int index, char *key)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL && ft_perror())
		return (1);
	free((*envp)[index]);
	(*envp)[index] = ft_strjoin(key, buffer);
	if (!(*envp)[index] && ft_perror())
		return (1);
	return (0);
}

static int	change_pwd_util(char ***envp, int o_pwd_i, int pwd_i)
{
	char	*pwd_str;
	char	*temp;

	if (pwd_i == -1)
	{
		temp = ft_strdup("OLDPWD=");
		if (!temp && ft_perror())
			return (1);
	}
	else
	{
		pwd_str = get_env_val("PWD", envp);
		temp = ft_strjoin("OLDPWD=", pwd_str);
		if (temp == NULL && ft_perror())
			return (1);
	}
	free((*envp)[o_pwd_i]);
	(*envp)[o_pwd_i] = temp;
	return (0);
}

int	change_pwd(char ***envp)
{
	char	*old_pwd_str;
	int		old_pwd_index;
	int		pwd_index;

	old_pwd_index = get_env_index("OLDPWD", 6, *envp);
	pwd_index = get_env_index("PWD", 3, *envp);
	if (old_pwd_index != -1)
	{
		old_pwd_str = get_env_val("OLDPWD", envp);
		if (old_pwd_str[0] == '\0' && pwd_index == -1)
		{
			if (replace_old_pwd(envp, old_pwd_index, "OLDPWD=") == 1)
				return (1);
		}
		else
			if (change_pwd_util(envp, old_pwd_index, pwd_index) == 1)
				return (1);
	}
	if (pwd_index != -1)
		return (replace_old_pwd(envp, pwd_index, "PWD="));
	return (0);
}
