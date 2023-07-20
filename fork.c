/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 23:30:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/20 23:30:25 by ktunchar         ###   ########.fr       */
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
	if (fd_infile != 0)
		dup2(fd_infile, STDIN_FILENO);
	if (fd_outfile != 1)
		dup2(fd_outfile, STDOUT_FILENO);
	if (ifd != 0 && fd_infile == 0)
		dup2(piped.fd[ifd - 1][0], STDIN_FILENO);
	if (ifd != piped.npipe && fd_outfile == 1)
		dup2(piped.fd[ifd][1], STDOUT_FILENO);	
}

void	ft_child(t_scmd *cmd, int pcnt, t_pipe pipe_data, char **env)
{
	t_buin buin_flag;
	
	ft_dup(pcnt, pipe_data, pipe_data.fd_in, pipe_data.fd_out);
	if (pcnt == 0 && pipe_data.fd_in != 0)
		close(pipe_data.fd_in);
	else if (pcnt == pipe_data.npipe && pipe_data.fd_out != 1)
		close(pipe_data.fd_in);
	close_pipe(pipe_data);
	if (is_built_in(cmd->cmd[0], &buin_flag))
	{
		exit (do_built_in(cmd, &buin_flag));
	}
	else
		execve(cmd->cmd[0], cmd->cmd, env);
}

void	do_fork(t_scmd *cmd, t_pipe pipe_data, int *status, char **env)
{
	int	process_cnt;
	int	*pid;
	t_scmd *curr;
	t_line *line;
	char **path;
	
	curr = cmd;
	process_cnt = 0;
	path = get_paths(env);
	pid = malloc(sizeof(int) * pipe_data.nprocess);
	while (process_cnt < pipe_data.nprocess)
	{
		line = apply_fd(curr->file);
		pipe_data.fd_in = line->fd_in;
		pipe_data.fd_out = line->fd_out;
		free(line);
		join_path(curr, path);
		if (line == NULL)
			return ;
		pid[process_cnt] = fork();
		if (pid[process_cnt] == 0)
			ft_child(curr, process_cnt, pipe_data, env);
		curr = curr->next;
		process_cnt += 1;
	}
	close_pipe(pipe_data);
	wait_all(pid, pipe_data, status);
	free(pid);
	ft_double_free(path);
}