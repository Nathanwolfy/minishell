/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:26:40 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:13:25 by nlederge         ###   ########.fr       */
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

int	cmd_split_count(t_tree *node)
{
	int		ct;
	t_tree	*it;

	ct = 1;
	it = node;
	while (it->right && (it->right)->type == R_CMD_SUFFIX)
	{
		ct++;
		it = it->right;
	}
	return (ct);
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
			return(free_split(cmd), infos->status = 1, NULL);
		it = it->right;
	}
	cmd[j] = NULL;
	cmd = check_get_cmd(cmd, envp, infos);
	return (cmd);
}

int	launch_cmd_sequence(t_tree *node, t_cmd_infos *infos, char **envp[], int ismain)
{
	char	**cmd;
	pid_t	fork_pid;
	int		is_builtin;

	is_builtin = check_builtins(node->content);
	if (ismain && is_builtin < 0)
		fork_pid = fork();
	else
		fork_pid = 0;
	if (fork_pid < 0)
		return (close_fds(infos, 0), print_error_from_errno(), 1);
	else if (is_builtin >= 0 && !ismain)
		return (exit_return(exec_builtin(is_builtin, node, envp, infos)));
	else if (is_builtin >= 0)
		return (exec_builtin(is_builtin, node, envp, infos));
	else if (fork_pid == 0)
	{
		if (!node)
			return (close_fds(infos, 0), print_error_from_errno(), 1);
		cmd = recreate_and_get_cmd(node, *envp, infos);
		if (!cmd)
			return (close_fds(infos, 0), exit_return(print_error_cmd(node->content, infos->status)));
		manage_fds_for_cmd(infos);
		if (execve(cmd[0], cmd, *envp) < 0)
			return (free_split(cmd), close_fds(infos, 0), exit_return(1));
	}
	return (close_fds(infos, 0), waitpid(fork_pid, &infos->status, 0), wait(NULL), 0);	
}
