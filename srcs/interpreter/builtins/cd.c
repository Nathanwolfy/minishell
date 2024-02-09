/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:33:35 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/09 12:37:05 by ehickman         ###   ########.fr       */
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

static int	change_pwd(char ***envp)
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
	if (!new_directory)
		return (1);
	r_val = change_directory(new_directory, envp);
	free(new_directory);
	return (r_val);
}

int	builtin_cd(char **cmd, char ***envp)
{
	if (!cmd[1])
		return (change_to_home(envp));
	else if (cmd[1][0] == '~' && (cmd[1][1] == '/' || cmd[1][1] == '\0'))
		return (expand_tilde(cmd[1], envp));
	else
		return (change_directory(cmd[1], envp));
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	char	buffer[PATH_MAX];
	(void)argc;
	builtin_env(env, 1);
	printf("%s\n", getcwd(buffer, PATH_MAX));
	builtin_cd(argv, &env);
	printf("%s\n", getcwd(buffer, PATH_MAX));
	builtin_env(env, 1);
}*/
