/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:33:35 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/16 18:12:32 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	change_directory(char *directory, char ***envp)
{
	if (chdir(directory) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(directory);
		return (1);
	}
	if (change_pwd(envp) == 1)
		return (1);
	return (0);
}

static int	change_to_home(char ***envp)
{
	char	*home;

	home = get_env_val("HOME", envp);
	if (home == (char *)-1)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	return (change_directory(home, envp));
}

static int	expand_tilde(char *directory, char ***envp)
{
	char	*home;
	char	*new_directory;
	int		r_val;

	home = get_env_val("HOME", envp);
	if (home == (char *)-1)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	new_directory = ft_strjoin(home, directory + 1);
	if (!new_directory && ft_perror())
		return (1);
	r_val = change_directory(new_directory, envp);
	free(new_directory);
	return (r_val);
}

int	builtin_cd(char **cmd, char ***envp)
{
	if (!cmd[1])
		return (change_to_home(envp));
	else if (cmd[2] != NULL)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	else if (cmd[1][0] == '~' && (cmd[1][1] == '/' || cmd[1][1] == '\0'))
		return (expand_tilde(cmd[1], envp));
	else
		return (change_directory(cmd[1], envp));
	return (0);
}
