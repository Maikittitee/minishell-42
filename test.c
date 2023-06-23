#include "exe.h"

int	main(int ac, char **av, char **env)
{
	int	**fd;
	int	n_pipe;
	int	pid;

	n_pipe = ac - 2;

	//malloc for pipe;
	fd = malloc(sizeof(int *) * n_pipe);

	int	i = 0;
	while (i < n_pipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < n_pipe)
	{
		pipe(fd[i]);
		i++;
	}
	
	pid = fork();
	if (pid == 0)
	{
		execve("")
	}
}