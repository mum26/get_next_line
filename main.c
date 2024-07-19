#include "get_next_line_bonus.h"
#include <libc.h>

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}

int	main(void)
{
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char	*line1;
	char	*line2;

	if (fd1 < 0)
		return (printf("fd1: No such file or direactory.\n"));
	if (fd2 < 0)
		return (printf("fd2: No such file or direactory.\n"));

	while(true)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 || !line2)
			break ;
		printf("%s%s", line1, line2);
		free(line1);
		free(line2);
	}
	close(fd1);
	close(fd2);
	return (0);
}
