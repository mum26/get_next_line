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

void	init_fp(t_file *fp, int fd)
{
	if (fp->_base)
		return ;
	fp->fd = fd;
	if (!fp->_base)
		return ;
	fp->_size = BUFFER_SIZE;
	fp->_cur = fp->_base;
	fp->line._base = (char *)malloc(sizeof(char) * LINE_SIZE);
	if (!fp->line._base)
		return ;
	fp->line._size = LINE_SIZE;
	fp->line._len = 0;
	fp->_flgs = 0;
}

size_t	ft_fread(t_file *fp)
{
	ssize_t	bytes_read;

	bytes_read = read(fp->fd, fp->buf_base, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		fp->buf_len = 0;
		free(fp->buf_base);
		if (fp->line_base)
			free(fp->line_base);
	}
	else
		fp->buf_len = (size_t)bytes_read;
	fp->buf_cur = fp->buf_base;
	
	return (fp->buf_len);
}

int	ft_fgetc(t_file *fp)
{
	if (fp->buf_len <= 0)
		fp->_len = read(fp->fd, fp->_base, BUFFER_SIZE);
	if (0 < fp->_len--)
		return ((unsigned char)*(fp->buf_cur++));

	if (fp->_len == EOF)
	{
		fp->_flgs = EOF;
		if(fp->line._base)
			free(fp->line._base);
		return (free(fp->_base), 0);
	}
	return (0);
}

size_t	append_char(char **dst, const char c, size_t dstsize)
{
	size_t	len;
	char	*p;

	if (!*dst || dstsize <= 0)
		return (0)
	p = NULL;
	len = ft_strlen(*dst);
	if (dstsize - 1 <= len)
	{
		dstsize *= 2;
		p = (char *)malloc(sizeof(char) * dstsize);
		if (!p)
			return (0);
		memcpy(p, *dst, len);
		free(*dst);
		*dst = p;
	}
	*(*dst + len++) = c;
	*(*dst + len) = '\0';
	return (dstsize);
}

#include <string.h>

char	*get_next_line(int fd)
{
	static t_file	fp;
	char			*p;

	init_fp(&fp, fd);
	if (!fp.line._base)
		return (NULL);
	if (fp._flgs == EOF)
		return (NULL);
	while(fp.flgs != EOF)
	{
		ft_fgetc(&fp);
		if (fp.line._size -1 <= fp.line._len)
		{
			fp.line_size *= 2;
			p = (char *)malloc(sizeof(char) * fp.line_size);
			if (!p)
				return (free(fp.line._base), NULL);
			memcpy(p, fp.line._base, fp.line._len);
			free(fp.line._base);
			fp.line._base = p;
		}
		*(fp.line_base + fp.line._len++) = *fp._cur++;
		fp._size--;
		if (*fp._cur++ == '\n')
			break ;
	}
	*(fp.line_base + fp.line_len++) = '\0';
	return (fp.line_base);
}

int main(void)
{
	int fd = open("main.c", O_RDONLY);
	char *p;

	while ((p = get_next_line(fd)))
	{
		printf("%s", p);
		free(p);
	}
	return (0);
}
