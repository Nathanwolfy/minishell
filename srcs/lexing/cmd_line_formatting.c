/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_formatting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:27:54 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/12 15:25:55 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	get_exit_status_len(int *flags, int *i, int exit_status)
{
	if (exit_status == 0)
		flags[*i] = -1;
	else
	{
		while (exit_status > 0)
		{
			flags[*i] -= 1;
			exit_status /= 10;
		}
	}
	*i += 2;
}

static void	replace_dquote_loop(int *i, char **envp, t_cmd_line_info *d)
{
	d->flags[*i] = 1;
	d->line[*i] = DQUOTE;
	*i += 1;
	while (d->line[*i])
	{
		if (d->line[*i] == '\"')
		{
			d->line[*i] = DQUOTE;
			d->flags[*i] = 1;
			*i += 1;
			return ;
		}
		if (d->line[*i] == '$' && d->line[*i + 1] == '?')
			get_exit_status_len(d->flags, i, d->exit_status);
		else if (d->line[*i] == '$')
			get_env_len(d->line, d->flags, i, envp);
		else
		{
			d->flags[*i] = 1;
			*i += 1;
		}
	}
}

static void	replace_squote_loop(char *line, int *flags, int *i)
{
	flags[*i] = 1;
	line[*i] = SQUOTE;
	*i += 1;
	while (line[*i])
	{
		flags[*i] = 1;
		if (line[*i] == '\'')
		{
			line[*i] = SQUOTE;
			*i += 1;
			return ;
		}
		*i += 1;
	}
}

static void	lexer_set_flags(char **envp, t_cmd_line_info *d)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(d->line);
	while (i < len)
	{
		if (i < len && d->line[i] == '\"')
			replace_dquote_loop(&i, envp, d);
		if (i < len && d->line[i] == '\'')
			replace_squote_loop(d->line, d->flags, &i);
		if (i < len && d->line[i] == '$' && d->line[i + 1] == '?')
			get_exit_status_len(d->flags, &i, d->exit_status);
		else if (i < len && d->line[i] == '$')
			get_env_len(d->line, d->flags, &i, envp);
		if (i < len && d->line[i] != '\"' \
		&& d->line[i] != '\'' && d->line[i] != '$')
		{
			d->flags[i] = 1;
			i++;
		}
	}
}

char	*format_cmd_line(char *line, char **envp, int exit_status)
{
	char			*new;
	t_cmd_line_info	*d;

	if (!line)
		return (NULL);
	d = malloc(sizeof(t_cmd_line_info));
	if (!d && ft_perror())
		return (NULL);
	d->flags = ft_calloc(ft_strlen(line), sizeof(int));
	if (!d->flags && ft_perror())
		return (NULL);
	d->line = ft_strdup(line);
	if (!d->line && ft_perror())
		return (free(d->flags), free(d), NULL);
	d->exit_status = exit_status;
	lexer_set_flags(envp, d);
	new = copy_flagged(d->line, d->flags, envp, d->exit_status);
	return (free(d->flags), free(d->line), free(d), new);
}
