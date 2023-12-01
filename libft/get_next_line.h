/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:52:16 by nlederge          #+#    #+#             */
/*   Updated: 2023/10/26 18:28:33 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*get_next_line_checked(int fd, ssize_t e, char *line);
void	*ft_movebuf_left_clear(char *buf, size_t start, size_t imax);
char	*ft_add_line(char *line, char *buf, size_t n);
char	*ft_strndup_gnl(const char *s, size_t n);
char	*ft_strnjoin_gnl(char *s1, char *s2, size_t n);
ssize_t	get_endli(char *s);

#endif
