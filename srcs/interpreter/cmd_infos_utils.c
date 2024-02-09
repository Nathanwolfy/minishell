/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_infos_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:49:19 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/08 20:14:56 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	reset_cmd_infos(t_cmd_infos *infos)
{
	if (!infos)
		return ;
	infos->pipe_readfd = -1;
	infos->use_pipe_read = 0;
	infos->pipe_writefd = -1;
	infos->use_pipe_write = 0;
	if (infos->fds_in)
		free(infos->fds_in);
	infos->fds_in = NULL;
	infos->fds_in_size = 0;
	if (infos->fds_out)
		free(infos->fds_out);
	infos->fds_out = NULL;
	infos->fds_out_size = 0;
	infos->status = 0;
}

static void	copy_fds(int *fds_new, int *fds_old, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fds_new[i] = fds_old[i];
		i++;
	}
}

int	add_fd(t_cmd_infos *infos, char in_out, int fd)
{
	int	*fds;

	if (in_out == 'i')
	{
		fds = ft_calloc(infos->fds_in_size + 1, sizeof(int));
		if (!fds)
			return (-1);
		copy_fds(fds, infos->fds_in, infos->fds_in_size);
		free(infos->fds_in);
		fds[infos->fds_in_size++] = fd;
		infos->fds_in = fds;
	}
	else if (in_out == 'o')
	{
		fds = ft_calloc(infos->fds_out_size + 1, sizeof(int));
		if (!fds)
			return (-1);
		copy_fds(fds, infos->fds_out, infos->fds_out_size);
		free(infos->fds_out);
		fds[infos->fds_out_size++] = fd;
		infos->fds_out = fds;
	}
	return (0);
}

void	close_fds(t_cmd_infos *infos, int notlast)
{
	int	k;

	if (!infos)
		return ;
	k = 0;
	while (k < infos->fds_in_size - notlast)
		close((infos->fds_in)[k++]);
	k = 0;
	while (k < infos->fds_out_size - notlast)
		close((infos->fds_out)[k++]);
}

void	manage_fds_for_cmd(t_cmd_infos *infos)
{
	close_fds(infos, 1);
	if (infos->fds_in_size > 0)
	{
		dup2((infos->fds_in)[infos->fds_in_size - 1], STDIN_FILENO);
		close((infos->fds_in)[infos->fds_in_size - 1]);
	}
	if (infos->fds_out_size > 0)
	{
		dup2((infos->fds_out)[infos->fds_out_size - 1], STDOUT_FILENO);
		close((infos->fds_out)[infos->fds_out_size - 1]);
	}
}
