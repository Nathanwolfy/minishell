/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:19:06 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:19:12 by nlederge         ###   ########.fr       */
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

static char	**check_get_cmd(char **cmdin, char **envp, t_cmd_infos *infos)
{
	char	**paths;
	char	*tmp;
	int		k;

	k = 0;
	paths = ft_split(find_path_var(envp), ':');
	if (!paths)
		return (free_split(cmdin), infos->status = 1, NULL);
	while (paths[k])
	{
		tmp = ft_strjoin_slash(paths[k], cmdin[0], 1);
		if (!tmp)
			return (infos->status = 1, NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (free(cmdin[0]), cmdin[0] = tmp, cmdin);
		free(tmp);
		k++;
	}
	tmp = ft_strjoin_slash("", cmdin[0], 0);
	if (!tmp)
		return (infos->status = 1, NULL);
	if (access(tmp, F_OK | X_OK) == 0)
		return (free(cmdin[0]), cmdin[0] = tmp, cmdin);
	return (free_split(cmdin), free(tmp), infos->status = 127, NULL);
}

char	**recreate_and_get_cmd(t_tree *node, char **envp, t_cmd_infos *infos)
{
	int		ct;
	int		j;
	char	**cmd;
	t_tree	*it;

	ct = cmd_split_count(node);
	cmd = ft_calloc(ct + 1, sizeof(char *));
	if (!cmd)
		return (infos->status = 1, NULL);
	j = 0;
	it = node;
	while (j < ct)
	{
		cmd[j] = ft_strdup(it->content);
		if (!cmd[j++])
			return (free_split(cmd), infos->status = 1, NULL);
		it = it->right;
	}
	cmd[j] = NULL;
	cmd = check_get_cmd(cmd, envp, infos);
	return (cmd);
}
