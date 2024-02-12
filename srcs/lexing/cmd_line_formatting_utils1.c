/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_formatting_utils1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:38:10 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/12 15:28:15 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	get_var_len(char *old, int *i)
{
	int	cursor;

	cursor = *i + 1;
	if (ft_isdigit(old[cursor]))
	{
		*i = cursor + 1;
		return (-1);
	}
	while (ft_isalpha(old[cursor]) \
	|| ft_isdigit(old[cursor]) || old[cursor] == '_')
		cursor++;
	return (cursor - *i - 1);
}

int	get_env_index(char *var, int len, char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], len) == 0 && envp[index][len] == '=')
			return (index);
		index++;
	}
	return (-1);
}

int	get_env_len(char *old, int *flags, int *i, char **envp)
{
	int	var_len;
	int	index;
	int	env_len;
	int	j;

	var_len = get_var_len(old, i);
	if (!var_len)
	{
		flags[*i] = 1;
		*i += 1;
		return (0);
	}
	else if (var_len == -1)
		return (0);
	index = get_env_index(old + *i + 1, var_len, envp);
	if (index == -1)
		return (*i += var_len + 1, 0);
	j = 0;
	while (envp[index][j] != '=')
		j++;
	env_len = 0;
	while (envp[index][++j] != '\0')
		env_len++;
	flags[*i] = -env_len;
	return (*i += var_len + 1, env_len);
}

void	copy_env_var(char *old, char *new, int *i, char **envp)
{
	int	var_len;
	int	index;
	int	new_i;
	int	env_i;

	new_i = 0;
	while (new[new_i] != 0)
		new_i++;
	var_len = get_var_len(old, i);
	if (!var_len)
		return ;
	index = get_env_index(old + *i + 1, var_len, envp);
	if (index == -1)
		return ;
	env_i = 0;
	while (envp[index][env_i] != '=')
		env_i++;
	env_i++;
	while (envp[index][env_i])
		new[new_i++] = envp[index][env_i++];
}
