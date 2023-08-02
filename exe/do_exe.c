/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:13:01 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/03 04:00:18 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	**get_paths(char **env)
{
	int		i;
	char	*path;
	char	**ret_path;

	path = NULL;
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