/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:12 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/09 02:27:04 by ktunchar         ###   ########.fr       */
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

void	start_pipe(t_pipe piped)
{
	int	i;

	i = 0;
	while (i < piped.npipe)
	{
		pipe(piped.fd[i]);
		i++;
	}
}

int	do_pipe(t_line *line, char **env) // incase of error should return -1
{
	int	status;
	t_pipe pipe_data;

	pipe_data.nprocess = cmdsize(*(line->cmd));
	// printf("the number of child process is %d\n", pipe_data.nprocess);
	pipe_data.npipe = pipe_data.nprocess - 1;
	pipe_data.fd = allocate_pipe(pipe_data.npipe);
	start_pipe(pipe_data);
	// if (!apply_fd(line))
	// 	return (-1);
	do_fork(line->cmd, line, pipe_data, &status, env);
	return (WEXITSTATUS(status));
}
