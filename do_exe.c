/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:13:01 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/19 18:42:21 by ktunchar         ###   ########.fr       */
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

int	get_cmd_path(t_cmd *cmd_d, char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = get_paths(env);
	if (access(cmd_d->arg[0], F_OK) == 0)
		return (1);
	// curr_path = *paths;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	return (1);
}

// int	exe_cmd(t_cmd *cmd_d, char **env, char **paths)
// {

// }