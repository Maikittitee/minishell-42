#include "exe.h"

int	join_path(t_cmd *cmd, char **paths)
{
	int	i;
	char	*check;
	char	*temp;

	i = 0;
	if (!cmd)
		return (0);
	if (access(cmd->arg[0], F_OK) == EXIT_SUCCESS)
		return (1);
	while (i != - 1 && paths[i])
	{
		check = ft_strjoin(paths[i], cmd->arg[0]);
		if (access(check, F_OK) == EXIT_SUCCESS)
		{
			temp = cmd->arg[0];
			cmd->arg[0] = ft_strdup(check);
			if (temp)
				free(temp);
			if (check)
				free(check);
			return (1);
		}
		if (check)
			free(check);
		i++;
	}

	return (0);
}

t_cmd	*new_cmd(char *arg, char **env)
{
	t_cmd	*cmd;
	char	**paths;

	paths = get_paths(env);
	(void)paths;
	cmd = malloc(sizeof(t_cmd));
	cmd->arg = ft_split(arg, ' ');
	cmd->fd = malloc(sizeof(t_fd));
	cmd->fd->in = 0;
	cmd->fd->out = 1;
	cmd->next = NULL;
	if (join_path(cmd, paths))
		printf("Join path OK\n");
	else
		printf("Join path KO\n");
	ft_double_free(paths);
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
	t_cmd	*curr;

	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_cmd;
	new_cmd->next = NULL;
	return (1);
}

void	print_cmd(t_cmd **head)
{
	t_cmd	*curr;

	curr = *head;
	while (curr)
	{
		printf("cmd:%s fd_in:%d fd_out:%d\n", \
		curr->arg[0], curr->fd->in, curr->fd->out);
		curr = curr->next;
	}
}