/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:50:52 by nlederge          #+#    #+#             */
/*   Updated: 2023/11/17 16:50:53 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/common.h"

static int	ft_word_size_adapted(char *str, int (*f)(int))
{
	int	size;

	size = 0;
	while (str[size] && !((*f)(str[size])))
		size++;
	return (size);
}

static int	get_size_adapted(char *line, int i)
{
	int	size;

	if (line[i] == '\'')
		size = ft_word_size_adapted(&line[i + 1], &ft_is_sq) + 2;
	else if (line[i] == '\"')
		size = ft_word_size_adapted(&line[i + 1], &ft_is_dq) + 2;
	else
		size = ft_word_size_adapted(&line[i], &ft_isspace);
	return (size);
}

static int	count_words_cmd(char *line, int to)
{
	int	ct;
	int	size;
	int	j;

	ct = 0;
	j = 0;
	while (line[j] && j < to)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		size = get_size_adapted(line, j);
		j += size;
		if (size != 0)
			ct++;
		else
			return (ct);
	}
	return (ct);
}

static char	*ft_strdup_len(char *str, int len)
{
	char	*ptr;
	int		k;

	k = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	else
	{
		while (k < len)
		{
			ptr[k] = *str;
			str++;
			k++;
		}
		ptr[k] = '\0';
		return (ptr);
	}
}

char	**ft_split_adapted(char *line, int to)
{
	char	**table;
	int		ct;
	int		k;

	ct = 0;
	k = 0;
	if (!line)
		return (NULL);
	table = malloc(sizeof(char *) * (count_words_cmd(line, to) + 1));
	if (table == NULL)
		return (NULL);
	while (line[k] && k < to)
	{
		while (line[k] && ft_isspace(line[k]))
			k++;
		if (get_size_adapted(line, k) == 0)
			break ;
		table[ct] = ft_strdup_len(&line[k], get_size_adapted(line, k));
		if (table[ct++] == NULL)
			return (free_split(table), NULL);
		k += get_size_adapted(line, k);
	}
	table[ct] = 0;
	return (table);
}
