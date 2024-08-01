/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:40 by sishige           #+#    #+#             */
/*   Updated: 2024/07/31 18:15:41 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_fgetc(t_file *fp)
{
	size_t	i;

	if (fp->_flgs < 0)
		return (EOF);
	if (fp->_len <= 0)
	{
		i = 0;
		fp->_len = read(fp->_file, fp->_base, BUFFER_SIZE);
		if (fp->_len <= 0)
		{
			fp->_flgs = -1;
			return (EOF);
		}
		fp->_flgs = 1;
		fp->_cur = fp->_base;
	}
	fp->_len--;
	return ((unsigned char)*fp->_cur++);
}

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*ret;
	size_t	cpy_size;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	ret = malloc(new_size);
	if (!ret)
	{
		free(ptr);
		return (NULL);
	}
	cpy_size = new_size;
	if (old_size < new_size)
		cpy_size = old_size;
	ft_memcpy(ret, ptr, cpy_size);
	return (free(ptr), ret);
}

//	On success, return the length of the string.
//	On failure, return -1.
int	ft_lputc(t_line *lp, int c)
{
	char	*new_base;

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
		new_base = (char *)ft_realloc(lp->_base, sizeof(char) * lp->_size * 2,
				sizeof(char) * lp->_size);
		if (!new_base)
			return (-1);
		lp->_base = new_base;
		lp->_size *= 2;
	}
	*(lp->_base + lp->_len++) = (unsigned char)c;
	*(lp->_base + lp->_len) = '\0';
	return (lp->_len);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_file			*fp;
	char			c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fp = find_fp(&lst, fd);
	if (!fp)
		return (ft_lstclear(&lst, &free), NULL);
	fp->line._base = NULL;
	fp->line._size = 0;
	fp->line._len = 0;
	fp->_flgs = 0;
	while (0 <= fp->_flgs)
	{
		c = ft_fgetc(fp);
		if (c != EOF)
			ft_lputc(&fp->line, c);
		if (c == '\n')
			break ;
	}
	if (!fp->line._base)
		return (ft_lstclear(&lst, &free), NULL);
	return (fp->line._base);
}
