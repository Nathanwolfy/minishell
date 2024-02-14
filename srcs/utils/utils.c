/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:56:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/14 16:33:57 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i] != 0)
		free(split[i++]);
	free(split);
}

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

/*void	print_table(int *table, int len)
{
	int	k;

	k = 0;
	while (k < len)
	{
		ft_putnbr_fd(table[k], STDERR_FILENO);
		ft_putstr_fd(" ", STDERR_FILENO);
		k++;
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}*/

int	return_status(t_cmd_infos *infos, int res)
{
	int	ret;

	if (infos && infos->status && WIFEXITED(infos->status))
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
