#include "exe.h"
typedef struct	s_pipe{
	int	npipe;
	int	nprocess;
	int	**fd;
	char **env;

} t_pipe;

void	start_pipe(t_pipe piped)
{
	int	i;

	i = 0;
	while (i < piped.npipe)
	{
		pipe(piped.fd[i]);
		i++;
	}
}

int	**allocate_pipe(t_pipe piped)
{
	int	**fd;
	int	i;

	if (piped.npipe == 0)
		return (NULL);

	fd = malloc(sizeof(int *) * piped.npipe);
	i = 0;
	while (i < piped.npipe)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (fd);
	

}

void	dupper(int ifd, t_pipe piped)
{
	if (ifd != 0)
		dup2(piped.fd[ifd - 1][0], STDIN_FILENO); //read
	else
		dup2(0, STDIN_FILENO); //read 0 may change to infile_fd

	if (ifd != piped.npipe)
		dup2(piped.fd[ifd][1], STDOUT_FILENO);	//write
	else
		dup2(1, STDOUT_FILENO); // write 1 may change to outfile_fd


		
}

void	ft_child(int ifd, t_pipe piped)
{
	char **c;

	c = ft_split("/bin/ls -l",' ');
	// dup2(0, STDIN_FILENO);
	// dup2(piped.fd[0][1], STDOUT_FILENO);
	dupper(ifd, piped);
	close(piped.fd[0][0]);
	close(piped.fd[0][1]);
	// dprintf(1, "h1\n");
	execve(c[0], c, piped.env);
}

void	ft_child2(int ifd, t_pipe piped)
{
	char **c;

	c = ft_split("/bin/sleep 10",' ');
	// dup2(piped.fd[0][0], STDIN_FILENO);
	// dup2(1, STDOUT_FILENO);
	dupper(ifd, piped);
	close(piped.fd[0][0]);
	close(piped.fd[0][1]);
	
	// dprintf(1, "h2\n");

	execve(c[0], c, piped.env);
}

int	main(int ac, char **av, char **env)
{
	t_pipe piped;
	int	*pid;
	int	i;
	int	pcnt;

	piped.env = env;
	piped.npipe = ac - 2; //1
	piped.nprocess = ac - 1; // 2
	piped.fd = allocate_pipe(piped); // malloc for pipe;
	start_pipe(piped); // map(pipe, fd);

	pcnt = 0;
	pid = malloc(sizeof(int) * piped.nprocess);

	// pid[0] = fork();
	// if (pid[0] == 0)
	// {
	// 	printf("hello1\n");
	// 	ft_child(0, piped);
	// }
	// pid[1] = fork();
	// if (pid[1] == 0)
	// {
	// 	printf("hello2\n");
	// 	ft_child2(1, piped);
	// }
	int	status;

	while (pcnt < piped.nprocess)
	{
		pid[pcnt] = fork();
		if (pcnt == 0 && pid[pcnt] == 0)
		{
			// printf("hello1\n");
			ft_child(pcnt, piped);
		}
		if (pcnt == 1 && pid[pcnt] == 0)
		{
			// printf("hello2\n");
			ft_child2(pcnt, piped);
		}
		pcnt += 1;

	}
	// close(piped.fd[0][0]);
	// close(piped.fd[0][1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);

	return (WEXITSTATUS(status));
}