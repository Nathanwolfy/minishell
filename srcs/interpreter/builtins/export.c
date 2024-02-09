/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:20:57 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/08 19:55:47 by nlederge         ###   ########.fr       */
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
			if (!new)
				return (-1);
			free(envp[i]);
			envp[i] = new;
			return (0);
		}
		i++;
	}
	return (1);
}

static char	**append_envp(char *old_envp[], char *content)
{
	char	**envp;
	int		ct;
	int		l;

	ct = get_double_arr_len(old_envp);
	envp = ft_calloc(ct + 2, sizeof(char *));
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
	envp[l] = ft_strdup(content);
	if (!envp[l])
		return (free_split(envp), NULL);
	envp[ct + 1] = NULL;
	return (envp);
}

static int	env_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s1[i] == s2[i])
		i++;
	return ((int)s1[i] - (int)s2[i]);
}

static void	sort_env(char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i + 1])
	{
		if (env_cmp(env[i], env[i + 1]) > 0)
		{
			tmp = env[i + 1];
			env[i + 1] = env[i];
			env[i] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static int	print_declare_envp(char **envp, int fd)
{
	char	**envp_cpy;
	int		i;
	int		j;

	i = 0;
	envp_cpy = copy_envp(envp);
	if (!envp_cpy)
		return (-1);
	sort_env(envp_cpy);
	while (envp_cpy[i])
	{
		ft_putstr_fd("declare -x", fd);
		j = -1;
		while (envp_cpy[i][++j])
		{
			ft_putchar_fd(envp_cpy[i][j], fd);
			if (envp_cpy[i][j] == '=')
				ft_putchar_fd(envp_cpy[i][j], fd);
		}
		ft_putstr_fd("\"\n", fd);
		i++;
	}
	return (free_split(envp_cpy), 0);
}

int	builtin_export(char **cmd, char ***envp, int fd)
{
	int		i;
	int		r_val;
	int		exit_status;

	exit_status = 0;
	if (!cmd || !envp || !*envp)
		return (exit_status);
	if (!cmd[1])
		return (print_declare_envp(*envp, fd));
	i = 1;
	while (cmd[i])
	{
		if (check_env_var_format(cmd[i], "export", fd) == -1)
		{
			exit_status = 1;
			i++;
			continue ;
		}
		r_val = modify_env_value(*envp, cmd[i]);
		if (r_val == -1)
			return (-1);
		else if (r_val == 1)
			*envp = append_envp(*envp, cmd[i]);
		if (!*envp)
			return (-1);
		i++;
	}
	return (exit_status);
}

/*int	main(int argc, char **argv, char **env)
{
	char **cmd;

	cmd = ft_calloc(5, sizeof(char *));
	cmd[0] = NULL;
	for (int i = 1; i < argc; i++)
		cmd[i - 1] = argv[i];
	builtin_env(env);
	printf("SADASDADASDASD\n");
	builtin_export(cmd, &env);
	printf("SDADSDASDASDASD\n");
	builtin_env(env);
}*/
