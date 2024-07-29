/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:40 by sishige           #+#    #+#             */
/*   Updated: 2024/07/29 23:48:25 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_fgetc(t_file *fp)
{
	if (fp->_flgs < 0)
		return (-1);
	if (fp->_len <= 0)
	{
		fp->_len = read(fp->_file, fp->_base, BUFFER_SIZE);
		if (fp->_len <= 0)
			return (fp->_flgs = -1, -1);
		fp->_flgs = 1;
		fp->_cur = fp->_base;
	}
	return (fp->_len--, *fp->_cur++);
}

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*ret;
	size_t	cpy_size;

	if (!new_size)
		return (free(ptr), NULL);
	if (!ptr)
		return (malloc(new_size));
	ret = malloc(new_size);
	if (!ret)
		return (free(ptr), NULL);
	if (new_size < old_size)
		cpy_size = new_size;
	else
		cpy_size = old_size;
	ft_memcpy(ret, ptr, cpy_size);
	return (free(ptr), ret);
}

//	On success, return the length of the string.
//	On failure, return -1.
int	ft_lputc(t_line *lp, int c)
{
	if (!lp)
		return (-1);
	if (!lp->_base)
	{
		lp->_base = (char *)malloc(sizeof(char) * LINE_SIZE);
		if (!lp->_base)
			return (-1);
		lp->_size = LINE_SIZE;
		lp->_len = 0;
	}
	if (lp->_size - 1 <= lp->_len)
	{
		lp->_base = (char *)ft_realloc(lp->_base, sizeof(char) * lp->_size * 2,
				sizeof(char) * lp->_size);
		if (!lp->_base)
			return (-1);
		lp->_size *= 2;
	}
	*(lp->_base + lp->_len++) = (unsigned char)c;
	*(lp->_base + lp->_len) = '\0';
	return (lp->_len);
}

char	*get_next_line(int fd)
{
	static t_file	fp = {0, "", BUFFER_SIZE, 0, fp._base, {NULL, 0, 0}, 0};
	char			c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fp._file = fd;
	fp.line._base = NULL;
	fp._flgs = 0;
	while (0 <= fp._flgs)
	{
		c = ft_fgetc(&fp);
		if (c != EOF)
			ft_lputc(&fp.line, c);
		if (c == '\n')
			break ;
	}
	if (!fp.line._base)
		return (NULL);
	return (fp.line._base);
}
