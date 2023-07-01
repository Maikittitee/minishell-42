/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:12 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/02 00:46:28 by ktunchar         ###   ########.fr       */
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


int	do_pipe(t_cmd **cmd, char **env)
{
	int	status;
	// int	infile_fd;
	// int	outfile_fd;
	t_pipe pipe_data;

	pipe_data.nprocess = cmdsize(*cmd);
	if (pipe_data.nprocess == 1)
		return (-1);
	pipe_data.npipe = pipe_data.nprocess - 1;
	pipe_data.fd = allocate_pipe(pipe_data.npipe);
	start_pipe(pipe_data);
	// infile_fd = open((*cmd)->infile, O_RDONLY);
	// outfile_fd = open((*cmd)->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	// if (infile_fd == -1 || outfile_fd == -1)
	// 	return (-1);
	do_fork(cmd, pipe_data, &status, env);
	return (status >> 8);
}
