/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:13:01 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/24 02:08:24 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	**get_paths(char **env)
{
	int		i;
	char	*path;
	char	**ret_path;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
		{
			path = ft_strtrim(env[i], "PATH=");
			break ;
		}
		i++;
	}
	ret_path = ft_split(path, ':');
	i = 0;
	while (ret_path[i])
	{
		ret_path[i] = ft_strjoin_free(ret_path[i], "/");
		i++;
	}
	free(path);
	return (ret_path);
}

int	executes(t_cmd **cmd, char **env)
{
	t_cmd *curr;
	
	curr = *cmd;
	while (curr)
	{
		execute(curr, env);
		curr = curr->next;
	}
	// clear_free_cmd(cmd);
	return (1);
	
}

int	execute(t_cmd *cmd, char **env)
{
	int	pid;
	int	status;

	dup2(cmd->fd->in, STDIN_FILENO);
	dup2( cmd->fd->out, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd->arg[0], cmd->arg, env);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
