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

#include "get_next_line_bonus.h"

t_file	*create_fp(int fd)
{
	t_file	*fp;

	if (fd < 0)
		return (NULL);
	fp = (t_file *)malloc(sizeof(t_file));
	if (!fp)
		return ( NULL);
	fp->fd = fd;
	fp->buf_size = BUFFER_SIZE;
	fp->buf = (char *)malloc(fp->buf_size * sizeof(char));
	if (!fp->buf)
		return (free(fp), NULL);
	return (fp);
}

void	destroy_fp(t_file *fp)
{
	if (fp)
	{
		if (fp->buf)
			free(fp->buf);
		free(fp);
		fp = NULL;
	}
}

char	ft_getc(int fd)
{
	char			c;
	static t_file	*fp[10];

	if (!fp[fd])
		fp[fd] = create_fp(fd);
	if (!fp[fd])
		return ('\0');
	if (!fp[fd]->buf_len)
	{
		fp[fd]->buf_len = read(fp[fd]->fd, fp[fd]->buf, BUFFER_SIZE);
		fp[fd]->buf_pos = 0;
	}
	if (0 <= --fp[fd]->buf_len)
		c = *(fp[fd]->buf + fp[fd]->buf_pos++);
	if (fp[fd]->buf_len < 0)
	{
		c = EOF;
		destroy_fp(fp[fd]);
	}
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
