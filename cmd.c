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
	check = ft_strjoin(paths[i], cmd->arg[0]);
	while (paths[i] && access(check, F_OK) != EXIT_SUCCESS)
	{
		i++;
		free(check);
		check = ft_strjoin(paths[i], cmd->arg[0]);
	}
	if (paths[i] == NULL)
		return (0);
	temp = cmd->arg[0];
	cmd->arg[0] = ft_strdup(check);
	free(check);
	free(temp);
	return (1);
}

t_cmd	*new_cmd(char *arg, char **env)
{
	t_cmd	*cmd;
	t_buin	dummy;
	char	**paths;

	// dummy = NULL;
	paths = get_paths(env);
	cmd = malloc(sizeof(t_cmd));
	cmd->arg = ft_split(arg, ' ');
	cmd->next = NULL;
	if (!is_built_in(cmd->arg[0], &dummy))
		join_path(cmd, paths);
	ft_double_free(paths);
	return (cmd);
}

int	cmd_create(t_cmd **head, t_cmd *new_cmd)
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
void	print_cmd(t_scmd **head)
{
	t_scmd	*curr;
	int		i;
	int		j;

	i = 1;
	curr = *head;
	while (curr != NULL)
	{
		j = 0;
		printf("%d.", i);
		while (curr->cmd[j])
		{
			printf("%s ", curr->cmd[j]);
			j++;
		}
		printf("\n");
		curr = curr->next;
		i++;
	}
}