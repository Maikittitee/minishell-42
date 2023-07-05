#include "exe.h"

int	main(int ac, char **av, char **env)
{
	int	status;
	char *s[4];
	s[0] = "/bin/cat";
	s[1] = "file2";
	s[2] = "file3";
	s[3] = NULL;
	int	infile_fd = open("file1", O_RDONLY);

	int	pid = fork();
	if (pid == 0)
	{


		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		execve(s[0],s ,env);
	}
	close(infile_fd);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));

}