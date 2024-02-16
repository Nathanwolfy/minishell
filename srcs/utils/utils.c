/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/16 15:54:54 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i] != 0)
		free(split[i++]);
	free(split);
	return (0);
}

void	close_fd_builtin(int fd)
{
	if (fd != STDOUT_FILENO && fd > 0)
		close(fd);
}

int	return_status(t_cmd_infos *infos, int res)
{
	int	ret;

	if (infos && WIFSIGNALED(infos->status))
		ret = 128 + WTERMSIG(infos->status);
	else if (infos && WIFEXITED(infos->status))
		ret = WEXITSTATUS(infos->status);
	else
		ret = res;
	free_data_infos(NULL, infos);
	return (ret);
}

int	exit_return(int res)
{
	exit(res);
	return (res);
}

void	free_data_infos(t_malloc_data *data, t_cmd_infos *infos)
{
	if (data && data->old_line)
		free(data->old_line);
	if (data && data->envp && *(data->envp))
		free_split(*(data->envp));
	if (data && data->ast)
		ft_treeclear(data->ast);
	if (infos && infos->fds_in)
		free(infos->fds_in);
	if (infos && infos->fds_out)
		free(infos->fds_out);
	if (infos)
		free(infos);
}
