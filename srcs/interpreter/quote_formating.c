/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:45:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/06 16:41:48 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	squote_loop(char *old, int *flags, int *i)
{
	flags[*i] = 0;
	while (old[++(*i)])
	{
		if (old[*i] == '\'')
		{
			flags[*i] = 0;
			*i += 1;
			return ;
		}
		flags[*i] = 1;
	}
}

static void	set_flags(char *old, int *flags, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(old);
	while (i < len)
	{
		if (i < len && old[i] == '\"')
			format_dquote_loop(old, flags, &i, envp);
		if (i < len && old[i] == '\'')
			squote_loop(old, flags, &i);
		if (i < len && old[i] == '$')
		{
			get_env_len(old, flags, &i, envp);
			i++;
		}
		if (i < len && old[i] != '\"' && old[i] != '\'' && old[i] != '$')
		{
			flags[i] = 1;
			i++;
		}
	}
}

int	get_flagged_len(char *old, int *flags)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (old[i])
	{
		if (flags[i] < 0)
			len += -flags[i];
		else
			len += flags[i];
		i++;
	}
	return (len);
}

char	*copy_flagged(char *old, int *flags, char **envp)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	len = get_flagged_len(old, flags);
	if (len == 0)
		return ((char *)-1);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (old[i])
	{
		if (flags[i] == 1)
		{
			new[j] = old[i];
			j++;
		}
		else if (flags[i] < 0)
		{
			copy_env_var(old, new, &i, envp);
			j += -flags[i];
		}
		i++;
	}
	return (new);
}

char	*format_quote(char *old, char **envp)
{
	char	*new;
	int		*flags;

	flags = ft_calloc(ft_strlen(old), sizeof(int));
	if (!flags)
		return (NULL);
	set_flags(old, flags, envp);
	new = copy_flagged(old, flags, envp);
	return (free(flags), new);
}
