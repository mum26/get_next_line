/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:59:18 by sishige           #+#    #+#             */
/*   Updated: 2024/07/30 23:43:32 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dst;
	s = src;
	if (d == s)
		return (dst);
	while (len--)
		*d++ = *s++;
	return (dst);
}

t_file	*init_fp(int fd)
{
	t_file	*fp;
	size_t	i;

	fp = (t_file *)malloc(sizeof(t_file));
	if (!fp)
		return (NULL);
	fp->_file = fd;
	i = 0;
	while (i < BUFFER_SIZE)
		*(fp->_base + i++) = '\0';
	fp->_size = BUFFER_SIZE;
	fp->_len = 0;
	fp->_cur = fp->_base;
	fp->line._base = NULL;
	fp->line._size = 0;
	fp->line._len = 0;
	fp->_flgs = 0;
	return (fp);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

t_file	*find_fp(t_list **lst, int fd)
{
	if (!lst)
		return (NULL);
	if (!*lst)
	{
		*lst = ft_lstnew(init_fp(fd));
		if (!*lst)
			return (NULL);
	}
	while ((*lst)->content->_file != fd)
	{
		if (!(*lst)->next)
		{
			(*lst)->next = ft_lstnew(init_fp(fd));
			if (!(*lst)->next)
				return (NULL);
		}
		*lst = (*lst)->next;
	}
	return ((*lst)->content);
}
