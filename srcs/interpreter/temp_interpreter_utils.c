/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_interpreter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:41:55 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 15:12:27 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

char	**check_get_cmd(char *cmdin)
{
	char	**cmd;
	char	**paths;
	char	*tmp;
	int		k;

	k = 0;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	cmdin = ft_strjoin("/", cmdin);
	if (!cmdin)
		return (NULL);
	cmd = ft_split_spaces(cmdin);
	if (!cmd)
		return (NULL);
	while (paths[k])
	{
		tmp = ft_strjoin(paths[k], cmd[0]);
		if (!tmp)
			return (free_split(cmd), NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (free(cmd[0]), cmd[0] = tmp, cmd);
		free(tmp);
		k++;
	}
	free(cmdin);
	free_split(cmd);
	return (NULL);
}
