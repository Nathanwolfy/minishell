/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_formating_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:38:10 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/02 12:02:03 by ehickman         ###   ########.fr       */
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
		return (-1);;
	}
	while (ft_isalpha(old[cursor]) || ft_isdigit(old[cursor]) || old[cursor] == '_')
		cursor++;
	return (cursor - *i - 1);
}

int	get_env_index(char *var, int len, char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], len) == 0)
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
		return (0);
	}
	else if (var_len == -1)
		return (0);
	index = get_env_index(old + *i + 1, var_len, envp);
	if (index == -1)
	{
		*i += var_len + 1;
		return (0);
	}
	j = 0;
	while (envp[index][j] != '=')
		j++;
	env_len = 0;
	while (envp[index][++j] != '\0')
		env_len++;
	flags[*i] = -env_len;
	*i += var_len + 1;
	return (env_len);
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
	index = get_env_index(old + *i + 1, var_len, envp);
	env_i = 0;
	while (envp[index][env_i] != '=')
		env_i++;
	env_i++;
	while(envp[index][env_i])
		new[new_i++] = envp[index][env_i++];
}

void	format_dquote_loop(char *old, int *flags, int *i, char **envp)
{
	flags[*i] = 0;
	while (old[++(*i)])
	{
		if (old[*i] == '\"')
		{
			flags[*i] = 0;
			*i += 1;
			return ;
		}
		else if (old[*i] == '$')
			get_env_len(old, flags, i, envp);
		else
			flags[*i] = 1;
	}
}
