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

#include "../includes/common.h"

static int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

static size_t	ft_word_size(char *str)
{
	size_t	size;

	size = 0;
	while (*str && !ft_isspace(*str))
	{
		size++;
		str++;
	}
	return (size);
}

static size_t	ft_word_count(char *str)
{
	size_t	ct;
	size_t	size;

	ct = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		size = ft_word_size(str);
		str += size;
		if (size != 0)
			ct++;
	}
	return (ct);
}

static char	*ft_strdup_len(char *str, size_t len)
{
	char	*ptr;
	size_t	k;

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

char	**ft_split_spaces(char *s)
{
	char	**table;
	size_t	size;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	table = malloc(sizeof(char *) * (ft_word_count(s) + 1));
	if (table == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		size = ft_word_size(s);
		if (size != 0)
		{
			table[i] = ft_strdup_len(s, size);
			if (table[i++] == NULL)
				return (free_split(table), NULL);
		}
		s += size;
	}
	table[i] = 0;
	return (table);
}
