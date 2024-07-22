/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:39:01 by sishige           #+#    #+#             */
/*   Updated: 2024/07/22 23:06:30 by sishige          ###   ########.fr       */
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

#define LINE_SIZE 128

typedef struct	s_file
{
	int		fd;			// file discrypter.
	char	buf_base[BUFFER_SIZE];	// pointer to the beginning of the read buffer.
	size_t	buf_size;	// buffer size.
	char	*buf_cur;	// pointer to current buffer.
	size_t	buf_len;	// remaining bytes.
	char	*line_base;	// pointer to the beginning of the line.
	size_t	line_size;	// line size.
	size_t	line_len;	// namber of chars in a line.
	ssize_t	flgs;
}				t_file;

char	*get_next_line(int fd);
void	create_fp(t_file *fp, int fd);
size_t	ft_fread(t_file *fp);
int		ft_fgetc(t_file *fp);

void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);

#endif
