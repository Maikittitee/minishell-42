#include "exe.h"


void	ft_double_free(char **s)
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
	if (!cmd)
		return ;
	ft_double_free(cmd->arg);
	ft_double_free(cmd->file);
	free(cmd->fd);
	free(cmd);
}

void	del_head(t_cmd **cmd)
{
	t_cmd	*tar;
	t_cmd	*next;

	if (!cmd)
		return ;
	if (!*cmd)
		return ;
	tar = *cmd;
	next = tar->next;
	(*cmd) = next;
	free_cmd(tar);
	
}

void	clear_free_cmd(t_cmd **cmd)
{
	t_cmd	*next;
	t_cmd	*curr;
	
	curr = *cmd;
	next = NULL;
	while (curr)
	{
		free_cmd(next);
		next = curr;
		curr = curr->next;
	}
	free_cmd(next);
	free(cmd);
}

