#include "get_next_line.h"
#include <libc.h>

__attribute__((destructor)) static void destructor(void)
{
	system("leaks -q a.out");
}

//// TEST: init_fp()
// void	test_init_fp(t_file *fp, int fd)
//{
//	init_fp(fp, fd);
//	printf("\nTEST: init_fp()\n");
//	printf("fd\t\t: %d\n", fp->_fd);
//	printf("base\t\t: %s\n", fp->_base);
//	printf("size\t\t: %zu\n", fp->_size);
//	printf("len\t\t: %ld\n", fp->_len);
//	printf("cur\t\t: %s\n", fp->_cur);
//	printf("line_base\t: %s\n", fp->line._base);
//	printf("line_size\t: %zu\n", fp->line._size);
//	printf("line_len\t: %zu\n", fp->line._len);
//	printf("flgs\t\t: %d\n", fp->_flgs);
//}
//
//// TEST: ft_fgetc()
// void	test_ft_fgetc(t_file *fp)
//{
//	printf("\nTEST: ft_getc()\n");
//	printf("c\t\t: %c\n", ft_fgetc(fp));
//}
//
//// TEST: append_char()
// void	test_append_char(t_file *fp)
//{
//	fp->line._size = append_char(&fp->line._base, *(fp->_cur - 1),
//			fp->line._size, fp->line._len);
//	printf("\nTEST: append_char()\n");
//	printf("line_base\t: %s\nline_size\t: %zu\n\n", fp->line._base,
//		fp->line._size);
//}
//
//// int	main(void)
////{
////	static t_file	fp;
////	int		fd;
////
////	fd = open("text.txt", O_RDONLY);
////	test_init_fp(&fp, fd);
////	test_ft_fgetc(&fp);
////	test_append_char(&fp);
////	free(fp.line._base);
////	close(fd);
////	return (0);
////}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*str;

	if (argc < 2)
		return (printf("引数でファイルパスを指定してください。"));
	fd = open(argv[1], O_RDONLY);
	for (size_t i = 0;; i++)
	{
		str = get_next_line(fd);
		printf("Line %3zu : %s", i, str);
		if (!str)
			break ;
		free(str);
		str = NULL;
	}
	close(fd);
	return (0);
}
