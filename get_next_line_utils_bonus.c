/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:59:18 by sishige           #+#    #+#             */
/*   Updated: 2024/07/24 19:09:13 by sishige          ###   ########.fr       */
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

	fp = (t_file *)malloc(sizeof(t_file));
	if (!fp)
		return (NULL);
	fp->_file = fd;
	*fp->_base = '\0';
	fp->_size = BUFFER_SIZE;
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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_file	*find_fp(t_list *lst, int fd)
{
	t_list	*find;
	if (!lst)
		return (NULL);
	find = lst;
	if (!find->content)
	{
		find->content = init_fp(fd);
		if (!find->content)
			return (NULL);
		return (find->content);
	}
	while (find->content->_file != fd)
	{
		if (!find->next)
		{
			find->next = ft_lstnew(NULL);
			if (!find->next)
				return (NULL);
			find->next->content = init_fp(fd);
			if (!find->next->content)
				return (NULL);
		}
		find = find->next;
	}
	return (find->content);
}
