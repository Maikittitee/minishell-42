/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 23:30:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/02 00:47:13 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"


void	close_pipe(t_pipe pipe_data)
{
	int	i;

	i = 0;
	while (i < pipe_data.npipe)
	{
		close(pipe_data.fd[i][0]);
		close(pipe_data.fd[i][1]);
		i++;
	}
	
}

void	wait_all(int *pid, t_pipe pipe_data, int *status)
{
	int	i;

	i = 0;
	while (i < pipe_data.nprocess - 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	waitpid(pid[i], status, 0);
	
}

void	ft_dup(int ifd, t_pipe piped, int fd_infile, int fd_outfile)
{
	if (ifd != 0)
		dup2(piped.fd[ifd - 1][0], STDIN_FILENO);
	else if (fd_infile != -1)
		dup2(fd_infile, STDIN_FILENO);

	if (ifd != piped.npipe)
		dup2(piped.fd[ifd][1], STDOUT_FILENO);
	else if (fd_outfile != -1)
		dup2(fd_outfile, STDOUT_FILENO);
}

void	ft_child(t_cmd *cmd, int ifd, t_pipe pipe_data, char **env)
{
	ft_dup(ifd, pipe_data, cmd->fd->in, cmd->fd->out);
	if (ifd == 0)
		close(cmd->fd->in);
	else if (ifd == pipe_data.npipe)
		close(cmd->fd->out);
	close_pipe(pipe_data);
	execve(cmd->arg[0], cmd->arg, env);
	
}

void	do_fork(t_cmd **cmd, t_pipe pipe_data, int *status, char **env)
{
	int	process_cnt;
	int	*pid;
	t_cmd *curr;
	
	curr = *cmd;
	process_cnt = 0;
	pid = malloc(sizeof(int) * pipe_data.nprocess);
	while (process_cnt < pipe_data.nprocess)
	{
		pid[process_cnt] = fork();
		if (pid[process_cnt] == 0)
		{
			ft_child(curr, process_cnt, pipe_data, env);
		}
		curr = curr->next;
		process_cnt += 1;
	}
	close_pipe(pipe_data);
	wait_all(pid, pipe_data, status);
}