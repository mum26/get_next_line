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

#define BUFFER_SIZE 1024

typedef struct s_file
{
	int		fd;
	char	mode;
	char	buf[BUFFER_SIZE];
	size_t	buf_size;
	size_t	buf_pos;
	size_t	buf_len;
} t_file;

char	*get_next_line(int fd);
t_file	*creat_stream(int fd);

#endif
