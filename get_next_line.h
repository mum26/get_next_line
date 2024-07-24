/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:39:01 by sishige           #+#    #+#             */
/*   Updated: 2024/07/18 21:40:28 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#define LINE_SIZE 1

typedef struct	s_line
{
	char	*_base;
	size_t	_size;
	size_t	_len;
}				t_line

typedef struct	s_file
{
	int		fd;		// file discrypter.
	char	_base[BUFFER_SIZE];	// pointer to the beginning of the read buffer.
	size_t	_size;	// buffer size.
	ssize_t	_len;	// length of buffer.
	char	*_cur;	// pointer to current buffer.
	t_line	line;	// line struct.
	int		_flgs;	// status of file pointer.
}				t_file;

char	*get_next_line(int fd);
void	init_fp(t_file *fp, int fd);
size_t	ft_fread(t_file *fp);
int		ft_fgetc(t_file *fp);
size_t	append_char(char **dst, char c, size_t dstsize);

void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif
