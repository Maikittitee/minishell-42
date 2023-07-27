/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 23:30:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/28 02:46:58 by ktunchar         ###   ########.fr       */
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
		if (pid[i] != -2)
		{
			if (status != NULL)
				waitpid(pid[i], status, 0);
			else
				waitpid(pid[i], NULL, 0);
		}
		i++;
	}
	
	// waitpid(pid[i], status, 0);
	
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
	
	ft_dup(pipe_data.pcnt, pipe_data, pipe_data.fd_in, pipe_data.fd_out);
	if (pipe_data.pcnt == 0 && pipe_data.fd_in != 0)
		close(pipe_data.fd_in);
	if (pipe_data.pcnt == pipe_data.npipe && pipe_data.fd_out != 1)
		close(pipe_data.fd_out);
	close_pipe(pipe_data);
	if (assign_buin(cmd->cmd[0], &buin_flag))
		do_built_in(cmd, &buin_flag);
	else
		execve(cmd->cmd[0], cmd->cmd, env);
}

int	is_do_in_parent(t_scmd *cmd, t_buin *buin)
{	
	if (!is_built_in(cmd->cmd[0]))
		return (0);
	if (ft_strncmp(cmd->cmd[0], "export", 7) ==0 && cmd->cmd[1] != NULL)
		return (*buin = e_export, 1);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (*buin = e_cd, 1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (*buin = e_unset, 1);
	else
		return (0);

	// should return 0 (success) or 1 (error)
	
}

int	do_in_parent(t_scmd *cmd, t_buin *buin)
{	
	if (*buin == e_export)
	{
		printf("hello export");
		return (EXIT_SUCCESS);
		// return (ft_export_arg(cmd->cmd));
	}
	else if (*buin == e_cd)
	{
		return (ft_cd(cmd->cmd));
	}
	else if (*buin == e_unset)
	{
		printf("hello unset");
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);

	// should return 0 (success) or 1 (error)
	
}
int	cmd_execute(t_scmd *cmd, t_pipe pipe_data, char **path, int	*status)
{
	t_buin buin;
	
	if (!is_built_in(cmd->cmd[0]))
		join_path(cmd, path);
	if (is_do_in_parent(cmd, &buin))
	{
		*status = do_in_parent(cmd, &buin);
		pipe_data.pid[pipe_data.pcnt] = -2;
	}
	else
	{
		pipe_data.pid[pipe_data.pcnt] = fork();
		if (pipe_data.pid[pipe_data.pcnt] == -1)
			return (raise_error("fork error", 0));
		if (pipe_data.pid[pipe_data.pcnt] == 0)
			ft_child(cmd, pipe_data, global_data.env_ptr);
		return (1);
	}
	return (1);
	
}

int	last_cmd_is_in_parent(int *pid, int n)
{
	int	i;

	i = 0;
	while (pid[i] && i < n - 1)
	{
		i++;
	}
	if (pid[i] == -2)
		return (1);
	return (0);	
	
}

int	do_fork(t_scmd *cmd, t_pipe pipe_data, char **env)
{
	t_scmd *curr;
	char **path;
	int	status;
	int	in_parent;
	
	curr = cmd;
	pipe_data.pcnt = 0;
	path = get_paths(env);
	pipe_data.pid = malloc(sizeof(int) * pipe_data.nprocess);
	while (pipe_data.pcnt < pipe_data.nprocess)
	{
		if (!apply_fd(curr->file, &pipe_data))
			return (0);
		if (!cmd_execute(curr, pipe_data, path, &status))
			return (0);
		curr = curr->next;
		pipe_data.pcnt += 1;
	}
	close_pipe(pipe_data);
	in_parent = last_cmd_is_in_parent(pipe_data.pid, pipe_data.nprocess); 
	if (in_parent)
		wait_all(pipe_data.pid, pipe_data, NULL);
	else
	{
		wait_all(pipe_data.pid, pipe_data, &status);
	}
	free(pipe_data.pid);
	ft_double_free(path);
	if (!in_parent)
		return (WEXITSTATUS(status));
	return (status);
}
