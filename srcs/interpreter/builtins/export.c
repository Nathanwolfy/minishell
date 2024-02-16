/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:20:57 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/16 13:28:00 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	modify_env_value(char **envp, char *content)
{
	char	*new;
	int		var_name_len;
	int		i;

	var_name_len = get_var_name_len(content);
	i = 0;
	while (envp[i])
	{
		if ((int)ft_strlen(envp[i]) >= var_name_len
			&& envp[i][var_name_len] == '='
			&& ft_strncmp(envp[i], content, var_name_len) == 0)
		{
			new = ft_strdup(content);
			if (!new && ft_perror())
				return (-1);
			free(envp[i]);
			envp[i] = new;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	append_envp(char **old_envp[], char *content)
{
	char	**envp;
	int		ct;
	int		l;

	ct = get_double_arr_len(*old_envp);
	envp = ft_calloc(ct + 2, sizeof(char *));
	if (!envp && ft_perror())
		return (1);
	l = 0;
	while (l < ct)
	{
		envp[l] = ft_strdup((*old_envp)[l]);
		if (!envp[l] && ft_perror())
			return (free_split(envp), 1);
		l++;
	}
	envp[l] = ft_strdup(content);
	if (!envp[l] && ft_perror())
		return (free_split(envp), 1);
	free_split(*old_envp);
	*old_envp = envp;
	return (0);
}

static int	export_each_arg(char **cmd, char ***envp)
{
	int	i;
	int	r_val;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd[i])
	{
		r_val = check_env_var_format(cmd[i], "export");
		if (r_val > 0)
		{
			if (r_val == 1)
				exit_status = 1;
			i++;
			continue ;
		}
		r_val = modify_env_value(*envp, cmd[i]);
		if (r_val == -1 || (r_val == 1 && append_envp(envp, cmd[i])))
		{
			i++;
			continue ;
		}
		i++;
	}
	return (exit_status);
}

int	builtin_export(char **cmd, char ***envp, int fd)
{
	if (!cmd || !envp || !*envp)
		return (0);
	if (!cmd[1])
		return (print_declare_envp(*envp, fd));
	return (export_each_arg(cmd, envp));
}
