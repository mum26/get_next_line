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

	fp = (t_file *)malloc(sizeof(t_file));
	if (!fp)
		return (NULL);
	fp->_file = fd;
	*fp->_base = '\0';
	fp->_size = BUFFER_SIZE;
	fp->_len = 0;
	fp->_cur = fp->_base;
	fp->line._base = NULL;
	fp->line._size = 0;
	fp->line._len = 0;
	fp->_flgs = 0;
	return (fp);
}

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *next;

    if (!lst || !del)
        return;

    while (*lst)
    {
        next = (*lst)->next;
        del((*lst)->content);
        free(*lst);
        *lst = next;
    }
    *lst = NULL;
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

t_file *find_fp(t_list **lst, int fd)
{
    t_list *current;

    if (!lst)
        return (NULL);

    if (!*lst)
    {
        *lst = ft_lstnew(init_fp(fd));
        if (!*lst)
            return (NULL);
    }

    current = *lst;

    while (current)
    {
        t_file *content = (t_file *)(current->content);
        if (content->_file == fd)
            return content;

        if (!current->next)
        {
            current->next = ft_lstnew(init_fp(fd));
            if (!current->next)
                return (NULL);
        }

        current = current->next;
    }
    
    return NULL;
}
