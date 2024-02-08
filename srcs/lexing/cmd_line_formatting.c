/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_formatting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:27:54 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/08 16:05:49 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*	0 == skip
	1 == copy;
	< 0 == expand var and number of chars
*/

static void	replace_dquote_loop(char *line, int *flags, int *i, char **envp)
{
	flags[*i] = 1;
	line[*i] = DQUOTE;
	*i += 1;
	while (line[*i])
	{
		if (line[*i] == '\"')
		{
			line[*i] = DQUOTE;
			flags[*i] = 1;
			*i += 1;
			return ;
		}
		else if (line[*i] == '$')
		{
			get_env_len(line, flags, i, envp);
			continue ;
		}
		else
			flags[*i] = 1;
		*i += 1;
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
	// error no closing quotes
	// just raise a flag and readline, ft_strjoin, if no opened quote remains stop, else repeat
}

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

static void	lexer_set_flags(char *line, int *flags, char **envp, int exit_status)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (i < len && line[i] == '\"')
			replace_dquote_loop(line, flags, &i, envp);
		if (i < len && line[i] == '\'')
			replace_squote_loop(line, flags, &i);
		if (i < len && line[i] == '$' && line[i + 1] == '?')
			get_exit_status_len(flags, &i, exit_status);
		else if (i < len && line[i] == '$')
			get_env_len(line, flags, &i, envp);
		if (i < len && line[i] != '\"' && line[i] != '\'' && line[i] != '$')
		{
			flags[i] = 1;
			i++;
		}
	}
}

char	*format_cmd_line(char *line, char **envp, int exit_status)
{
	int		*flags;
	char	*copy;
	char	*new;

	if (!line)
		return (NULL);
	flags = ft_calloc(ft_strlen(line), sizeof(int));
	if (!flags)
		return (NULL); //error
	copy = ft_strdup(line);
	if (!copy)
		return (free(flags), NULL);
	lexer_set_flags(copy, flags, envp, exit_status);
	new = copy_flagged(copy, flags, envp, exit_status);
	return (free(flags), free(copy), new);
}
