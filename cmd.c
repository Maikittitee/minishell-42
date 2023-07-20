#include "exe.h"

int	join_path(t_scmd *cmd, char **paths)
{
	int	i;
	char	*check;
	char	*temp;

	i = 0;
	if (!cmd)
		return (0);
	if (access(cmd->cmd[0], F_OK) == EXIT_SUCCESS)
		return (1);
	check = ft_strjoin(paths[i], cmd->cmd[0]);
	while (paths[i] && access(check, F_OK) != EXIT_SUCCESS)
	{
		i++;
		free(check);
		check = ft_strjoin(paths[i], cmd->cmd[0]);
	}
	if (paths[i] == NULL)
	{
		free(check);
		return (0);
	}
	temp = cmd->cmd[0];
	cmd->cmd[0] = ft_strdup(check);
	free(check);
	free(temp);
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