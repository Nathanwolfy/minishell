/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:04:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/08 09:30:50 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	find_index_to_skip(char *var, char **envp)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (envp[i])
	{
		if (get_var_name_len(envp[i]) == var_len
			&& ft_strncmp(var, envp[i], var_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	**dup_envp(char **envp, int index_to_skip)
{
	int		i;
	int		j;
	int		ct;
	char	**new;

	i = 0;
	j = 0;
	ct = get_double_arr_len(envp);
	new = ft_calloc(ct, sizeof(char *));
	if (!new)
		return (free_split(envp), NULL);
	while (envp[j])
	{
		if (j == index_to_skip)
		{
			j++;
			continue ;
		}
		new[i] = ft_strdup(envp[j]);
		if (!new)
			return (free_split(new), free_split(envp), NULL);
		i++;
		j++;
	}
	return (new);
}
static char	**remove_var(char *var, char **envp)
{
	int		index_to_skip;

	index_to_skip = find_index_to_skip(var, envp);
	if (index_to_skip == -1)
		return (envp);
	return (dup_envp(envp, index_to_skip));
}

int	builtin_unset(char **cmd, char ***envp, int fd)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!cmd || !*cmd || !envp || !*envp)
		return (exit_status);
	while (cmd[i])
	{
		if (check_env_var_format(cmd[i], "unset", fd) == -1)
		{
			exit_status = 1;
			i++;
			continue ;
		}
		*envp = remove_var(cmd[i], *envp);
		if (!*envp)
			return (-1);
		i++;
	}
	return (exit_status);
}

/*int	main(int argc, char **argv, char **env)
{
	char	**cmd;

	cmd = ft_calloc(5, sizeof(char *));
	for (int i = 0; i < argc - 1; i++)
	{
		cmd[i] = ft_strdup(argv[i + 1]);
	}
	builtin_env(env);
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	builtin_unset(cmd, &env);
	printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	builtin_env(env);
}*/

