/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:13:01 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/12 00:38:01 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
	
char **get_paths(char **env)
{
	int	i;
	char *str_path;
	char **ret;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			str_path = ft_strdup(env[i]);
			break;
		}
		i++;
	}
	ret = ft_split(str_path + 5, ':');
	free(str_path);
	return (ret);
}

char *get_cmd_path(t_cmd *cmd_d, char **paths)
{
	
}

int	exe_cmd(t_cmd *cmd_d, char **env, char **paths)
{
	
	cmd_d->cmd = get_cmd_path(cmd_d, paths)
	
	// execute()
	return (1);
	
}