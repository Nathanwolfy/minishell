/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/14 15:45:17 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	print_tokens(t_token **tokens)
{
	t_token	*t;

	if (!tokens)
		return ;
	t = *tokens;
	while (t)
	{
		printf("content = %s, type = %d\n", t->content, t->type);
		t = t->next;
	}
}

void	close_fd_builtin(int fd)
{
	if (fd != STDOUT_FILENO && fd > 0)
		close(fd);
}

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_putendl_fd(split[i], STDERR_FILENO);
		i++;
	}
}

int	return_status(t_cmd_infos *infos, int res)
{
	if (WIFEXITED(infos->status))
		return (WEXITSTATUS(infos->status));
	else
		return (res);
}

int	exit_return(int res)
{
	exit(res);
	return (res);
}
