#include "exe.h"

t_cmd	*new_cmd(char *arg, char **env)
{
	t_cmd	*cmd;
	char	**paths;

	paths = get_paths(env);
	cmd = malloc(sizeof(t_cmd));
	cmd->arg = ft_split(arg, ' ');
	cmd->fd = malloc(sizeof(t_fd));
	cmd->fd->in = 0;
	cmd->fd->out = 1;
	cmd->next = NULL;
	return (cmd);
}

int	create_cmd(t_cmd **head, t_cmd *new_cmd)
{
	if (!head)
		return (0);
	*head = new_cmd;
	return (1);
}

int	cmd_add(t_cmd **head, t_cmd *new_cmd)
{
	if ()

}