/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishige <sishige@student.42tokyo.j>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:40 by sishige           #+#    #+#             */
/*   Updated: 2024/07/18 21:38:02 by sishige          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_file *create_stream(int fd)
{
	t_file	*stream;

	if (fd < 0)
		return (NULL);
	stream = (t_file *)ft_calloc(1, sizeof(t_file));
	if (!stream)
		return ( NULL);
	stream->fd = fd;
	stream->buf_size = BUFFER_SIZE;
	stream->buffer = (char *)ft_calloc(stream->buf_size, sizeof(char));
	if (!stream->buffer)
		return (free(stream), NULL);
	return (stream);
}

void *destroy_stream(t_file *stream)
{
	if (stream)
	{
		if (stream->buffer)
			free(stream->buffer);
		free(stream);
		stream = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_file	*stream;
	char			line[BUFFER_SIZE];
	ssize_t			bytes_read;

	if (fd < 0)
		return (NULL);
	stream = create_stream(fd);
	if (!stream)
		return (NULL);
	while (true)
	{
		if (stream->buf_length <= stream->buf_position)
			bytes_read = read(stream->fd, stream->buffer, stream->buf_size);
		if (bytes_read <= 0)
			return (NULL);
		stream->buf_position = 0;
		stream->buf_length = bytes_read;
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf(No such file or directory.));
	line = NULL;
	while (true)
	{
		
	}
}

