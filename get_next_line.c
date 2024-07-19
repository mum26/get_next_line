/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:40 by sishige           #+#    #+#             */
/*   Updated: 2024/07/18 21:38:02 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	ft_getc(int fd)
{
	static char		buf[BUFFER_SIZE];
	static size_t	buf_pos;
	static int		bytes_read;
	char			c;

	if (!bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf_pos = 0;
	}

	if (0 <= --bytes_read)
		c = *(buf + buf_pos++);
	if (bytes_read < 0)
		c = EOF;
	return (c);
}

size_t	ft_putc(char **str, char c)
{
	char	*new_str;
	size_t	len;

	if (!c)
		return (0);
	len = 0;
	if (*str)
		len = ft_strlen(*str);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (free(str), 0);
	ft_memcpy(new_str, *str, len);
	*(new_str + len) = c;
	if (!len)
		free(*str);
	*str = new_str;
	return (1);
}

char	*get_next_line(int fd)
{
	char	*result;
	char	c;

	if (fd < 0)
		return (NULL);
	result = NULL;
	while(true)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		ft_putc(&result, c);
		if (c == '\n')
			break ;
	}
	ft_putc(&result, '\0');
	return (result);
}
