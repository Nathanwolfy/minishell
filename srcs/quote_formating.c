/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:45:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/01/31 15:36:03 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*	0 == skip
	1 == copy
	< 0 == expand and expand_size
*/

static int	get_var_len(char *old, int *i)
{
	int	cursor;

	cursor = *i + 1;
	if (ft_isdigit(old[cursor]))
	{
		while (ft_isdigit(old[cursor]))
			cursor++;
		*i = cursor - 1;
		return (-1);;
	}
	while (ft_isalpha(old[cursor]) || ft_isdigit(old[cursor]) || old[cursor] == '_')
		cursor++;
	return (cursor - *i - 1);
}

static int	get_env_index(char *var, int len, char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(var, envp[index], len) == 0)
			return (index);
		index++;
	}
	return (-1);
}

static int	get_env_len(char *old, int *flags, int *i, char **envp)
{
	int	var_len;
	int	index;
	int	env_len;
	int	j;

	var_len = get_var_len(old, i);
	if (!var_len)
	{
		flags[*i] = 1;
		return (0);
	}
	else if (var_len == -1)
		return (0);
	index = get_env_index(old + *i + 1, var_len, envp);
	if (index == -1)
		return (0);
	j = 0;
	while (envp[index][j] != '=')
		j++;
	env_len = 0;
	while (envp[index][++j] != '\0')
		env_len++;
	flags[*i] = -env_len;
	*i += var_len + 1;
	return (env_len);
}

static void	copy_env(char *old, char *new, int *i, char **envp)
{
	int	var_len;
	int	index;
	int	new_i;
	int	env_i;

	new_i = 0;
	while (new[new_i] != 0)
		new_i++;
	var_len = get_var_len(old, i);
	index = get_env_index(old + *i + 1, var_len, envp);
	env_i = 0;
	while (envp[index][env_i] != '=')
		env_i++;
	env_i++;
	while(envp[index][env_i])
		new[new_i++] = envp[index][env_i++];
}

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

static void	dquote_loop(char *old, int *flags, int *i, char **envp)
{
	(void)envp;
	flags[*i] = 0;
	while (old[++(*i)])
	{
		if (old[*i] == '\"')
		{
			flags[*i] = 0;
			*i += 1;
			return ;
		}
		else if (old[*i] == '$')
			get_env_len(old, flags, i, envp);
		else
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
			dquote_loop(old, flags, &i, envp);
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

static int	get_flagged_len(char *old, int *flags)
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

static char	*copy_flagged(char *old, int *flags, char **envp)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	len = get_flagged_len(old, flags);
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
			copy_env(old, new, &i, envp);
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
	if (!new)
		return (NULL);
	return (new);
}

/*int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	printf("|  BASIC QUOTE TESTS  |\n");
	printf("\"\'\" => %s\n", format_quote("\"\'\"", env));
	printf("\"test1\" => %s\n", format_quote("\"test1\"", env));
	printf("\"\'test2\" => %s\n", format_quote("\"\'test2\"", env));
	printf("\"\'test3\'\" => %s\n", format_quote("\"\'test3\'\"", env));
	printf("\'\"test4\' => %s\n", format_quote("\'\"test4\'", env));
	printf("\'\"\"tes\'\'t5\' => %s\n", format_quote("\'\"\"tes\'\'t5\'", env));
	printf("mini\'test6\' => %s\n", format_quote("mini\'test6\'", env));
	printf("\"mini\'test7\'\" => %s\n", format_quote("\"mini\'test7\'\"", env));
	printf("\"mini\'test8\" => %s\n", format_quote("\"mini\'test8\"", env));
	printf("|  ENV VAR TESTS  |\n");
	printf("\"$OUI test8\" => %s\n", format_quote("\"$OUI test8\"", env));
	printf("\"$OUItest8\" => %s\n", format_quote("\"$OUItest8\"", env));
	printf("\"$1OUI test9\" => %s\n", format_quote("\"$1OUI test9\"", env));
	printf("\"mini\'\'$ test10\" => %s\n", format_quote("\"mini\'\'$ test10\"", env));
	printf("$ (avec espace) => %s\n", format_quote("$ (avec espace)", env));
	printf("$$ => %s\n", format_quote("$$", env));
	printf("$OUI => %s\n", format_quote("$OUI", env));
	printf("$$OUI => %s\n", format_quote("$$OUI", env));
	printf("$$$OUI => %s\n", format_quote("$$$OUI", env));
	printf("\'$OUI\' => %s\n", format_quote("\'$OUI\'", env));
	printf("\"$OUI\" => %s\n", format_quote("\"$OUI\"", env));
}*/
