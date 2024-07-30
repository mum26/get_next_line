/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 21:32:54 by sishige           #+#    #+#             */
/*   Updated: 2024/07/30 23:18:21 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define LINE_SIZE 1

typedef struct s_line
{
	char	*_base;
	size_t	_size;
	size_t	_len;
}				t_line;

//	Explanation of _flgs.
//	 1: Start reading file.
//	 0: File has not been read.
//	-1: End of file(EOF).
typedef struct s_file
{
	int		_file;
	char	_base[BUFFER_SIZE];
	size_t	_size;
	ssize_t	_len;
	char	*_cur;
	t_line	line;
	int		_flgs;
}				t_file;

typedef struct s_list
{
	t_file			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
int		ft_fgetc(t_file *fp);
int		ft_lputc(t_line *lp, int c);
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size);

t_file	*init_fp(int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_file	*find_fp(t_list **lst, int fd);
void	*ft_memcpy(void *dst, const void *src, size_t len);

#endif
