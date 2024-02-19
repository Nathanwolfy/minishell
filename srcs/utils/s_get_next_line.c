/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_get_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:49:41 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/19 12:13:04 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*s_get_next_line_checked(int fd, ssize_t e, char *line)
{
	static char	buf[1024][BUFFER_SIZE + 1];

	while (e > 0)
	{
		e = get_endli(buf[fd]);
		if (e == -1)
			line = ft_add_line(line, buf[fd], BUFFER_SIZE + 1);
		else if (e >= 0)
		{
			line = ft_add_line(line, buf[fd], e + 1);
			if (e < BUFFER_SIZE)
				ft_movebuf_left_clear(buf[fd], e + 1, BUFFER_SIZE);
			else
				ft_bzero(buf[fd], BUFFER_SIZE + 1);
			return (line);
		}
		e = read(fd, buf[fd], BUFFER_SIZE);
		if (e == 0)
			return (free(line), ft_bzero(buf[fd], BUFFER_SIZE + 1), \
		(char *) -1);
		if (e < 0)
			return (free(line), ft_bzero(buf[fd], BUFFER_SIZE + 1), NULL);
		buf[fd][e] = '\0';
	}
	return (line);
}

char	*s_get_next_line(int fd)
{
	char	*line;
	ssize_t	e;

	line = NULL;
	e = 1;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	return (s_get_next_line_checked(fd, e, line));
}
