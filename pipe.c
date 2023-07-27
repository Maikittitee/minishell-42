/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:12 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/28 02:39:57 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	**allocate_pipe(int npipe)
{
	int	i;
	int	**buffer;

	i = 0;
	if (npipe == 0)
		return (NULL);
	buffer = malloc(sizeof(int *) * npipe);
	while (i < npipe)
	{
		buffer[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (buffer);
}

int	start_pipe(t_pipe piped)
{
	int	i;

	i = 0;
	while (i < piped.npipe)
	{
		if (pipe(piped.fd[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void	free_pipe(int **fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	do_pipe(t_scmd *cmd, char **env)
{
	t_pipe pipe_data;

	pipe_data.nprocess = cmdsize(cmd);
	pipe_data.npipe = pipe_data.nprocess - 1;
	pipe_data.fd = allocate_pipe(pipe_data.npipe);
	if (!start_pipe(pipe_data))
	{
		free_pipe(pipe_data.fd, pipe_data.npipe);
		return (raise_error("pipe error", 0));
	}
	global_data.return_code = do_fork(cmd, pipe_data, env);
	free_pipe(pipe_data.fd, pipe_data.npipe);

	// return that have no errr
	return (1);
}
