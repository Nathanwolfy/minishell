/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:27:54 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/02 13:32:59 by ehickman         ###   ########.fr       */
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

static void	lexer_set_flags(char *line, int *flags, char **envp)
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
		if (i < len && line[i] == '$')
			get_env_len(line, flags, &i, envp);
		if (i < len && line[i] != '\"' && line[i] != '\'' && line[i] != '$')
		{
			flags[i] = 1;
			i++;
		}
	}
}

char	*lexer_expand_var_replace_quotes(char *line, char **envp)
{
	int		*flags;
	char	*new;

	flags = ft_calloc(ft_strlen(line), sizeof(int));
	if (!flags)
		return (NULL); //error
	lexer_set_flags(line, flags, envp);
	new = copy_flagged(line, flags, envp);
	//for (int i = 0; line[i]; i++)
	//	printf("%c : %d\n", line[i], flags[i]);
	return (free(flags), free(line), new);
}
