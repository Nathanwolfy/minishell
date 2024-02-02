/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:45:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/02 10:58:14 by ehickman         ###   ########.fr       */
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
