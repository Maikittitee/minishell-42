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