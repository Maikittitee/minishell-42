/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:13:56 by ktunchar          #+#    #+#             */
/*   Updated: 2023/02/28 15:23:03 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
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

int	is_access_cmd(char **path, char **cmd, char *pure_cmd)
{
	char	*temp;
	int		i;
	int		access_flag;

	if (!cmd)
		return (0);
	i = 0;
	access_flag = 0;
	temp = cmd[0];
	while (!access_flag && path[i])
	{
		cmd[0] = ft_strjoin(path[i], pure_cmd);
		if (temp)
			free(temp);
		temp = cmd[0];
		if (access(cmd[0], F_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_find_cmd(t_pipex *pipex, char **av)
{
	static char	*p_cmd[2];

	if (av[2][0] != 0)
	{
		pipex->cmd1 = ft_split(av[2], ' ');
		p_cmd[0] = ft_strdup((pipex->cmd1)[0]);
	}
	if (av[3][0] != 0)
	{
		pipex->cmd2 = ft_split(av[3], ' ');
		p_cmd[1] = ft_strdup((pipex->cmd2)[0]);
	}
	if (pipex->cmd1 && access((pipex->cmd1)[0], F_OK) == 0)
		pipex->access_flag1 = 1;
	if (pipex->cmd2 && access((pipex->cmd2)[0], F_OK) == 0)
		pipex->access_flag2 = 1;
	if (!pipex->access_flag1)
		pipex->access_flag1 = is_access_cmd(pipex->path, pipex->cmd1, p_cmd[0]);
	if (!pipex->access_flag2)
		pipex->access_flag2 = is_access_cmd(pipex->path, pipex->cmd2, p_cmd[1]);
	if (p_cmd[0])
		free(p_cmd[0]);
	if (p_cmd[1])
		free(p_cmd[1]);
}

void	init_pipex(t_pipex *pipex, char **env)
{
	pipex->access_flag1 = 0;
	pipex->access_flag2 = 0;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->path = get_path(env);
}
