/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:38:04 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/18 17:32:56 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*map;
	unsigned int	l;

	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	map = malloc(sizeof(char) * (l + 1));
	if (!map)
		return (NULL);
	l = 0;
	while (s[l])
	{
		map[l] = (*f)(l, s[l]);
		l++;
	}
	map[l] = '\0';
	return (map);
}
