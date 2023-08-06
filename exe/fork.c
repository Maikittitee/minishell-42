/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 23:30:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 21:17:21 by ktunchar         ###   ########.fr       */
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
	while (i < pipe_data.nprocess)
	{
		waitpid(pid[i], status, 0);
		i++;
	}
}

void	ft_dup(int ifd, t_pipe piped, int fd_infile, int fd_outfile)
{
	if (fd_infile != 0)
		dup2(fd_infile, STDIN_FILENO);
	if (fd_outfile != 1)
		dup2(fd_outfile, STDOUT_FILENO);
	if (ifd != 0 && fd_infile == 0)
		dup2(piped.fd[ifd - 1][0], STDIN_FILENO);
	if (ifd != piped.npipe && fd_outfile == 1)
		dup2(piped.fd[ifd][1], STDOUT_FILENO);
}

int	cmd_execute(t_scmd *cmd, t_pipe pipe_data)
{
	pipe_data.pid[pipe_data.pcnt] = fork();
	if (pipe_data.pid[pipe_data.pcnt] == -1)
		return (raise_error("fork error", KERNEL_ERR));
	if (pipe_data.pid[pipe_data.pcnt] == 0)
		ft_child(cmd, pipe_data, g_global_data.env_ptr);
	return (1);
}

int	do_fork(t_scmd *cmd, t_pipe pipe_data)
{
	t_scmd	*curr;
	t_buin	dummy;
	int		status;

	curr = cmd;
	if (pipe_data.npipe == 0 && is_do_in_parent(cmd, &dummy))
	{
		close_pipe(pipe_data);
		return (do_in_parent(cmd, &dummy));
	}
	pipe_data.pcnt = 0;
	pipe_data.path = get_paths(g_global_data.env_ptr);
	pipe_data.pid = malloc(sizeof(int) * pipe_data.nprocess);
	while (curr && pipe_data.pcnt < pipe_data.nprocess)
	{
		if (!cmd_execute(curr, pipe_data))
			return (1);
		curr = curr->next;
		pipe_data.pcnt += 1;
	}
	close_pipe(pipe_data);
	wait_all(pipe_data.pid, pipe_data, &status);
	free(pipe_data.pid);
	ft_double_free(pipe_data.path);
	return (WEXITSTATUS(status));
}
