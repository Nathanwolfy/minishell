/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:51:37 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/26 18:23:18 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup_gnl(const char *s, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	while (s[i] && i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strnjoin_gnl(char *s1, char *s2, size_t n)
{
	char	*join;
	size_t	size;
	size_t	i;
	size_t	k;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strndup_gnl(s2, n));
	size = ft_strlen(s1) + n;
	i = 0;
	join = ft_calloc(size + 1, sizeof(char));
	if (!join)
		return (NULL);
	while (*s1)
		join[i++] = *(s1++);
	k = 0;
	while (s2[k] && k < n)
		join[i++] = s2[k++];
	join[i] = '\0';
	return (join);
}

ssize_t	get_endli(char *s)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-2);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i);
	i = 0;
	while (s[i])
		i++;
	if (i == 0)
		return (-2);
	else
		return (-1);
}
