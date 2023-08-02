#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	char *c[2];

	c[0] = "/bin/ls";
	c[1] = NULL;
	chdir("lib");
	execve(c[0], c, env);
}