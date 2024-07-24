/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:39:01 by sishige           #+#    #+#             */
/*   Updated: 2024/07/25 01:29:36 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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

/*
	Explanation of _flgs.
	 1: Start reading file.
	 0: File has not been read.
	-1: End of file(EOF).
	-2: Line._base memory allocation failure.
*/

typedef struct s_file
{
	int		_fd;
	char	_base[BUFFER_SIZE];
	size_t	_size;
	ssize_t	_len;
	char	*_cur;
	t_line	line;
	int		_flgs;
}				t_file;

char	*get_next_line(int fd);
void	init_fp(t_file *fp, int fd);
size_t	ft_fread(t_file *fp);
int		ft_fgetc(t_file *fp);
size_t	append_char(char **dst, char c, size_t dstsize, size_t dstlen);

void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);

#endif
