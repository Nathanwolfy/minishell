/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:49:07 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/17 21:36:12 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;
	size_t	t;

	t = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (t / nmemb != size)
		return (NULL);
	r = malloc(t);
	if (!r)
		return (NULL);
	ft_bzero(r, t);
	return (r);
}
