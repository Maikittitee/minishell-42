#include "exe.h"

int	main()
{
	int	fd[2];
	int	pid;
	int	x;

	pipe(fd);
	printf("IN PIPE is %d\n", fd[0]);
	printf("OUT PIPE is %d\n", fd[1]);

	pid = fork();
	if (pid == 0)
	{
		read(fd[1], &x, 4);
		printf("hello from child 1 and x is %d\n", x);

	}
	// x = 6;
	// write(fd[0], &x, 4);
}