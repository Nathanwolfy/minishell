/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:19:06 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 18:57:00 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*ft_strjoin_slash(char *s1, char *s2, int addslash)
{
	char	*join;
	size_t	size;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	join = malloc(sizeof(char) * (size + 1 + addslash));
	if (!join)
		return (NULL);
	while (*s1)
		join[i++] = *(s1++);
	if (addslash)
		join[i++] = '/';
	while (*s2)
		join[i++] = *(s2++);
	join[i] = '\0';
	return (join);
}

static char	*find_path_var(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

static char	*correct_tmp_cmd(char **cmdin, char **paths, int k)
{
	char	*tmp;

	if (paths[k][0] == '\0' && ft_strchr(cmdin[0], '/') != NULL)
		tmp = ft_strdup(cmdin[0]);
	else if (paths[k][0] == '\0' && ft_strchr(cmdin[0], '/') == NULL)
		tmp = ft_strjoin_slash(".", cmdin[0], 1);
	else
		tmp = ft_strjoin_slash(paths[k], cmdin[0], 1);
	return (tmp);
}

static char	**check_get_cmd(char **cmdin, char **envp, t_cmd_infos *infos)
{
	char	**paths;
	char	*tmp;
	int		k;

	k = -1;
	paths = ft_split_null(find_path_var(envp), ':');
	if (!paths)
		return (free_split(cmdin), err(infos), NULL);
	while (paths[++k])
	{
		tmp = correct_tmp_cmd(cmdin, paths, k);
		if (!tmp)
			return (free_split(cmdin), free_split(paths), err(infos), NULL);
		if (fnot_ok_xok(tmp))
			return (ft_perror_str(tmp), free(tmp), free_split(cmdin), \
			free_split(paths), infos->status = 126, infos->error = 1, NULL);
		else if (!f_ok(tmp) && !x_ok(tmp))
			return (free(cmdin[0]), cmdin[0] = tmp, free_split(paths), cmdin);
		free(tmp);
	}
	if (!free_split(paths) && ft_strchr(cmdin[0], '/') && fnot_ok_xok(cmdin[0]))
		return (ft_perror_str(cmdin[0]), free_split(cmdin), deny(infos), NULL);
	else if (ft_strchr(cmdin[0], '/') && !f_ok(cmdin[0]) && !x_ok(cmdin[0]))
		return (cmdin);
	else if (ft_strchr(cmdin[0], '/') && f_ok(cmdin[0]))
		return (no_such_file(infos, cmdin[0]), free_split(cmdin), NULL);
	return (cmd_not_found(infos, cmdin[0]), free_split(cmdin), NULL);
}

static int	is_directory(char *cmdname, t_cmd_infos *infos)
{
	struct stat	path_stat;

	if (stat(cmdname, &path_stat) != 0)
		return (0);
   	else if (S_ISDIR(path_stat.st_mode) && ft_strchr(cmdname, '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmdname, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		infos->status = 126;
		infos->error = 1;
		return (1);
	}
	return (0);
}

char	**recreate_and_get_cmd(t_tree *node, char **envp, t_cmd_infos *infos)
{
	int		ct;
	int		j;
	char	**cmd;
	t_tree	*it;

	if (is_directory(node->content, infos))
		return (NULL);
	ct = cmd_split_count(node);
	cmd = ft_calloc(ct + 1, sizeof(char *));
	if (!cmd)
		return (err(infos), NULL);
	j = 0;
	it = node;
	while (j < ct)
	{
		cmd[j] = ft_strdup(it->content);
		if (!cmd[j++])
			return (free_split(cmd), err(infos), NULL);
		it = it->right;
	}
	cmd[j] = NULL;
	return (check_get_cmd(cmd, envp, infos));
}
