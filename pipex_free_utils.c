/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:18:55 by ktunchar          #+#    #+#             */
/*   Updated: 2023/02/28 14:25:37 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*buffer;

	buffer = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (buffer);
}

void	ft_double_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_free_pipex(t_pipex *pipex)
{
	if (pipex->cmd1)
		ft_double_free(pipex->cmd1);
	if (pipex->cmd2)
		ft_double_free(pipex->cmd2);
	if (pipex->path)
		ft_double_free(pipex->path);
}
