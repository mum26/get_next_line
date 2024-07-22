/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:40 by sishige           #+#    #+#             */
/*   Updated: 2024/07/22 23:06:42 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	init_fp(t_file *fp, int fd)
{
	fp->fd = fd;
	fp->buf_size = BUFFER_SIZE;
	fp->buf_cur = 0;
	fp->buf_len = 0;
	fp->line_base = NULL;
	fp->line_size = 0;
	fp->line_len = 0;
	fp->flgs = 0;
	return (0);
}

size_t	ft_fread(t_file *fp)
{
	ssize_t	bytes_read;

	bytes_read = read(fp->fd, fp->buf_base, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		fp->buf_len = 0;
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
		if (!ft_fread(fp))
			return (EOF);
	if (0 < fp->buf_len--)
		return ((unsigned char)*(fp->buf_cur++));
	return (0);
}

#include <string.h>

char	*get_next_line(int fd)
{
	static t_file	fp;
	char			c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (fp.fd != fd)
		init_fp(&fp, fd);
	fp.line_base = NULL;
	while(fp.flgs != EOF)
	{
		c = (unsigned char)ft_fgetc(&fp);
		if (c == EOF)
			fp.flgs = EOF;
		if (!fp.line_base)
		{
			if (!fp.line_size)
				fp.line_size = LINE_SIZE;
			fp.line_len = 0;
			fp.line_base = (char *)malloc(sizeof(char) * fp.line_size);
			if (!fp.line_base)
				return (NULL);
		}
		if (fp.line_size - 1 <= fp.line_len)
		{
			fp.line_size *= 2;
			fp.line_base = (char *)realloc(fp.line_base, sizeof(char) * fp.line_size);
		}
		if (c != EOF)
			*(fp.line_base + fp.line_len++) = c;
		if (c == '\n')
			break ;
	}
	*(fp.line_base + fp.line_len) = '\0';
	return (fp.line_base);
}

int main(void)
{
	int fd = open("a.txt", O_RDONLY);
	char *p;

	while ((p = get_next_line(fd)))
	{
		printf("%s", p);
		free(p);
	}
	return (0);
}

/*
char	*get_next_line(int fd)
{
	char			*result;
	static t_file	*fp;
	size_t			start;

	result = NULL;
	if (fd < 0)
		return (NULL);
	if (!fp)
		fp = create_fp(fd);
	if (!fp)
		return (NULL);
	if (fp->buf_len <= fp->buf_pos)
		if (!ft_fread(fp))
			return (destroy_fp(fp), NULL);
	start = fp->buf_pos;
	while (*(fp->buf + fp->buf_pos++))
		if (*(fp->buf + fp->buf_pos) == '\n')
			break ;
	result = (char *)malloc(sizeof(char) * fp->buf_pos++ - start + 1);
	ft_memcpy(result, fp->buf + start, fp->buf_pos - start);
	*(result + fp->buf_pos - start) = '\0';
	return (result);
}
*/
