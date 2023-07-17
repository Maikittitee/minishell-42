#include "exe.h"

void	ft_free_file(t_file **file)
{
	int	i;

	i = 0;
	if (!file)
		return ;
	while (file[i])
	{
		if (file[i]->filename)
			free(file[i]->filename);
		if (file[i])
			free(file[i]);
		i++;
	}
	if (file)
		free(file);
}

int	ft_max(int *fd, int size)
{
	int	i;
	int	max;

	i = 0;
	if (!fd)
		return (-1);
	max = fd[0];
	while (i < size)
	{

		if (fd[i] > max)
			max = fd[i];
		i++;
	}
	return (max);
}