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

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

typedef struct s_file
{
	int		fd;
	char	mode;
	char	*buf;
	size_t	buf_size;
	size_t	buf_pos;
	ssize_t	buf_len;
} t_file;

char	*get_next_line(int fd);
char	ft_getc(int fd);
size_t	ft_putc(char **str, char c);
t_file	*create_fp(int fd);
void	destroy_fp(t_file *fp);

void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);

#endif
