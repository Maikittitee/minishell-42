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

void	close_used(int	ifd, t_pipe piped, int in, int out)
{
}

// firsst one
void	dupper(int ifd, t_pipe piped, int fd_infile, int fd_outfile)
{
	if (ifd != 0)
		dup2(piped.fd[ifd - 1][0], STDIN_FILENO); //read
	else if (fd_infile != -1)
		dup2(fd_infile, STDIN_FILENO); //read 0 may change to infile_fd

	if (ifd != piped.npipe)
		dup2(piped.fd[ifd][1], STDOUT_FILENO);	//write
	else if (fd_outfile != -1)
		dup2(fd_outfile, STDOUT_FILENO); // write 1 may change to outfile_fd


		
}

void	ft_child(int ifd, t_pipe piped, char *cmd, int in, int out)
{
	char **c;

	c = ft_split(cmd,' ');
	dupper(ifd, piped, in, out);
	if (ifd == 0)
		close(in);
	else if (ifd == piped.npipe)
		close(out);
	close(piped.fd[0][0]);
	close(piped.fd[0][1]);
	execve(c[0], c, piped.env);
}

void	close_unused(int ifd, t_pipe piped)
{

}


void	closepipe(t_pipe piped)
{
	int	i;

	i = 0;
	while (i < piped.npipe)
	{
		close(piped.fd[i][0]);
		close(piped.fd[i][1]);
		i++;
	}

}

int	main(int ac, char **av, char **env)
{
	t_pipe piped;
	int	*pid;
	int	i;
	int	pcnt;

	piped.env = env;
	i = 1;
	piped.npipe = ac - 2; //1
	piped.nprocess = ac - 1; // 2
	piped.fd = allocate_pipe(piped); // malloc for pipe;
	start_pipe(piped); // map(pipe, fd);

	pcnt = 0;
	pid = malloc(sizeof(int) * piped.nprocess);

	int	status;
	int	in_fd = open("infile", O_RDONLY);
	int	out_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0777);

	while (pcnt < piped.nprocess)
	{
		pid[pcnt] = fork();
		if (pid[pcnt] == 0)
		{
			dprintf(2, "i is %d this is the cmd %s\n",i, av[i]);
			if (pcnt == 0)
				ft_child(pcnt, piped, av[i], in_fd, piped.fd[0][1]);
			if (pcnt == 1)
				ft_child(pcnt, piped, av[i], piped.fd[0][0], out_fd);
		}
		pcnt += 1;
		i++;

	}
	// close(piped.fd[0]);
	// close(piped.fd[1]);
	closepipe(piped);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);

	return (WEXITSTATUS(status));
}