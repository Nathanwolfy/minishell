/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:09:36 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/06 17:05:25 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	get_double_arr_len(char *old_envp[])
{
	int	k;

	if (!old_envp)
		return (0);
	k = 0;
	while (old_envp[k])
		k++;
	return (k);
}

int	get_var_name_len(char *var)
{
	int	var_name_len;

	var_name_len = 0;
	while (var[var_name_len] && var[var_name_len] != '=')
		var_name_len++;
	return (var_name_len);
}

static void	ft_put_invalid_identifier(char *str, char *str1)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": `", 1);
	ft_putstr_fd(str1, 1);
	ft_putstr_fd("' : not a valid identifier\n", 1);
}

int	check_env_var_format(char *content, char *cmd)
{
	int	i;

	i = 0;
	if (!content || (!ft_isalpha(content[i]) && content[i] != '_'))
	{
		ft_put_invalid_identifier(cmd, content);
		return (-1);
	}
	while (content[i])
	{
		if (content[i] == '=')
			return (0);
		if (!ft_isalpha(content[i]) && !ft_isdigit(content[i])
			&& content[i] != '_')
		{
			ft_put_invalid_identifier(cmd, content);
			return (-1);
		}
		i++;
	}
	if (cmd[0] == 'u')
		return (0);
	return (-1);
}

