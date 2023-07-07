#include "exe.h"


void	ft_double_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_double_free(cmd->arg);
	free(cmd);
}

void	clear_free_cmd(t_cmd **cmd)
{
	t_cmd	*next;
	t_cmd	*curr;

	curr = *cmd;
	next = curr->next;
	while (curr)
	{
		free_cmd(curr);
		curr = next;
		next = next->next;
	}
	free_cmd(curr);
}

