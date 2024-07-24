#include "get_next_line.h"


#include <libc.h>

__attribute__((destructor))
static void	destructor(void) {
	system("leaks -q a.out");
}


int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
        size_t i = 1;

        if (argc < 2)
		return (printf("arg tarinai.\n"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (printf("fd1: No such file or direactory.\n"));
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("line %5zu :%s", i, line);
		free(line);
                i++;
        }
        close(fd);
	return (0);
}
