/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 23:30:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/03 20:29:21 by ktunchar         ###   ########.fr       */
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

void	ft_child(t_scmd *cmd, t_pipe pipe_data, char **env)
{
	t_buin buin_flag;
	int	open_file_status;

	open_file_status = apply_fd(cmd->file, &pipe_data);
	if (open_file_status != EXIT_SUCCESS)
			exit(open_file_status);
	ft_dup(pipe_data.pcnt, pipe_data, pipe_data.fd_in, pipe_data.fd_out);
	if (pipe_data.pcnt == 0 && pipe_data.fd_in != 0)
		close(pipe_data.fd_in);
	if (pipe_data.pcnt == pipe_data.npipe && pipe_data.fd_out != 1)
		close(pipe_data.fd_out);
	close_pipe(pipe_data);
	if (!is_built_in(cmd->cmd[0]) && !join_path(cmd, pipe_data.path))
		exit(raise_error(cmd->cmd[0], NOCMD_ERR));
	if (assign_buin(cmd->cmd[0], &buin_flag))
		do_built_in(cmd, &buin_flag);
	else
		execve(cmd->cmd[0], cmd->cmd, env);
}

int	is_do_in_parent(t_scmd *cmd, t_buin *buin)
{
	if (!is_built_in(cmd->cmd[0]))
		return (0);
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0 && cmd->cmd[1])
		return (*buin = e_export, 1);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (*buin = e_cd, 1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (*buin = e_unset, 1);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		return (*buin = e_exit, 1);
	else
		return (0);

	// should return 0 (true) or 1 (false)

}

int	do_in_parent(t_scmd *cmd, t_buin *buin)
{
	t_pipe pipe_data;
	int	open_file_status;
	open_file_status = apply_fd(cmd->file, &pipe_data);
	if (open_file_status != EXIT_SUCCESS)
			return (open_file_status);				
	if (*buin == e_export)
		return (ft_export(cmd->cmd));
	else if (*buin == e_cd)
		return (ft_cd(cmd->cmd));
	else if (*buin == e_unset)
		return (ft_unset(cmd->cmd));
	else if (*buin == e_exit)
		return (ft_exit(cmd->cmd));
	else
		return (EXIT_FAILURE);

	// should return 0 (success) or 1 (error)

}
int	cmd_execute(t_scmd *cmd, t_pipe pipe_data)
{
	pipe_data.pid[pipe_data.pcnt] = fork();
	if (pipe_data.pid[pipe_data.pcnt] == -1)
		return (raise_error("fork error", KERNEL_ERR));
	if (pipe_data.pid[pipe_data.pcnt] == 0)
		ft_child(cmd, pipe_data, global_data.env_ptr);
	return (1);

}

int	do_fork(t_scmd *cmd, t_pipe pipe_data)
{
	t_scmd *curr;
	t_buin dummy;
	int	status;

	curr = cmd;
	if (pipe_data.npipe == 0 && is_do_in_parent(cmd, &dummy))
	{
		close_pipe(pipe_data);
		return (do_in_parent(cmd, &dummy));
	}
	pipe_data.pcnt = 0;
	pipe_data.path = get_paths(global_data.env_ptr);
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
