#include "exe.h"


void	ft_double_free(void **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_cmd(t_cmd *cmd)
{
	ft_double_free(cmd->arg);
	ft_double_free(cmd->file);
	free(cmd->fd);
	free(cmd);
}

