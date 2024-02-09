/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:54:48 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/09 13:56:16 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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

int	print_declare_envp(char **envp, int fd)
{
	char	**envp_cpy;
	int		i;
	int		j;

	i = 0;
	envp_cpy = copy_envp(envp);
	if (!envp_cpy)
		return (1);
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
