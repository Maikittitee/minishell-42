/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 23:30:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/18 17:29:58 by ktunchar         ###   ########.fr       */
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
	else if (fd_infile != 0)
		dup2(fd_infile, STDIN_FILENO);
	if (ifd != piped.npipe)
		dup2(piped.fd[ifd][1], STDOUT_FILENO);
	else if (fd_outfile != 1)
		dup2(fd_outfile, STDOUT_FILENO);
}

void	ft_child(t_cmd *cmd, int fd_in, int fd_out, int pcnt, t_pipe pipe_data, char **env)
{
	t_buin buin_flag;
	
	// if (!ft_dup_to_file() )
	// else
	ft_dup(pcnt, pipe_data, fd_in, fd_out);
	if (pcnt == 0 && fd_in != 0)
		close(fd_in);
	else if (pcnt == pipe_data.npipe && fd_out != 1)
		close(fd_out);
	close_pipe(pipe_data);
	printf("cmd is %s\n", cmd->arg[0]);
	if (is_built_in(cmd->arg[0], &buin_flag))
	{
		printf("this is built in\n");
		exit (do_built_in(cmd, &buin_flag));
	}
	else
		execve(cmd->arg[0], cmd->arg, env);
}

void	do_fork(t_scmd *cmd, t_pipe pipe_data, int *status, char **env)
{
	int	process_cnt;
	int	*pid;
	t_scmd *curr;
	t_line line;
	
	curr = cmd;
	process_cnt = 0;
	pid = malloc(sizeof(int) * pipe_data.nprocess);
	while (process_cnt < pipe_data.nprocess)
	{
		if (apply_fd(&line, curr->file) != -1)
			return (-1);
		pid[process_cnt] = fork();
		if (pid[process_cnt] == 0)
			ft_child(curr, line.fd_in, line.fd_out, process_cnt, pipe_data, env);
		curr = curr->next;
		process_cnt += 1;
	}
	close_pipe(pipe_data);
	wait_all(pid, pipe_data, status);
}