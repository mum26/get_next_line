#include "get_next_line_bonus.h"

int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (0);
	int fd = open(argv[1], O_RDONLY);
	char	*line;

	if (fd < 0)
		return (printf("No such file or direactory.\n"));
	while(true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
