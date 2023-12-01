/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:16:01 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/20 17:09:38 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && (unsigned char)c != s[i])
	{
		i++;
	}
	if ((unsigned char)c == s[i])
		return ((char *)(s + i));
	return (NULL);
}
