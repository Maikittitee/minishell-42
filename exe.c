#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	char *arg[3];

	arg[0] = "echo";
	arg[1] = getenv("ZSH"); // -> use when try to find buildin variable
	arg[2] = NULL;

	execve("/bin/echo", arg, env);
}