/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:40 by sishige           #+#    #+#             */
/*   Updated: 2024/07/25 01:30:19 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_fp(t_file *fp, int fd)
{
	fp->line._base = NULL;
	fp->line._size = 0;
	fp->line._len = 0;
	if (fp->_flgs != 0)
		return ;
	fp->_fd = fd;
	*fp->_base = '\0';
	fp->_size = BUFFER_SIZE;
	fp->_len = 0;
	fp->_cur = fp->_base;
	fp->_flgs = 0;
}

int	ft_fgetc(t_file *fp)
{
	if (fp->_flgs < 0)
		return (-1);
	if (fp->_len <= 0)
	{
		fp->_len = read(fp->_fd, fp->_base, BUFFER_SIZE);
		if (fp->_len <= 0)
		{
			fp->_flgs = -1;
			return (-1);
		}
		fp->_flgs = 1;
		fp->_cur = fp->_base;
	}
	fp->_len--;
	return (*fp->_cur);
}

size_t	append_char(char **dst, const char c, size_t dstsize, size_t dstlen)
{
	char	*p;

	if (!dst || dstsize < 0 || dstlen < 0)
		return (0);
	if (!*dst)
	{
		*dst = (char *)malloc(sizeof(char) * dstsize++);
		if (!dst)
			return (0);
		**dst = '\0';
	}
	if (dstsize - 1 <= dstlen)
	{
		dstsize *= 2;
		p = (char *)malloc(sizeof(char) * dstsize);
		if (!p)
			return (0);
		ft_memcpy(p, *dst, dstlen);
		free(*dst);
		*dst = p;
	}
	*(*dst + dstlen++) = c;
	*(*dst + dstlen) = '\0';
	return (dstsize);
}

char	*get_next_line(int fd)
{
	static t_file	fp;
	char			c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	init_fp(&fp, fd);
	if (fp._flgs < 0)
		return (NULL);
	while (true)
	{
		c = ft_fgetc(&fp);
		if (c == EOF)
			return (NULL) ;
		fp.line._size =  append_char(&fp.line._base, c, fp.line._size, fp.line._len++);
		if (*fp._cur++ == '\n')
			break ;
	}
	*(fp.line._base + fp.line._len++) = '\0';
	return (fp.line._base);
}
