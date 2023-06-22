#include "exe.h"

int	main()
{
	int	fd[2];
	int	pid;

	pipe(fd);
	printf("IN PIPE is %d\n", fd[0]);
	printf("OUT PIPE is %d\n", fd[1]);
}