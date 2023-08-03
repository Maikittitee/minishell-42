/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:13:01 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 00:42:25 by ksaelim          ###   ########.fr       */
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
	if (env[i] == NULL)
		return (NULL);
	ret_path = ft_split(path, ':');
	i = 0;
	while (ret_path[i])
	{
		ret_path[i] = ft_strjoin_free(ret_path[i], "/");
		i++;
	}
	return (free(path), ret_path);
}
