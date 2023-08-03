/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentnchild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 02:12:30 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 02:16:48 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_child(t_scmd *cmd, t_pipe pipe_data, char **env)
{
	t_buin	buin_flag;
	int		open_file_status;

	open_file_status = apply_fd(cmd->file, &pipe_data);
	if (open_file_status != EXIT_SUCCESS)
		exit(open_file_status);
	if (!cmd->cmd)
		exit(EXIT_FAILURE);
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
	else if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
		exit(raise_error(cmd->cmd[0], 125));
}

int	is_do_in_parent(t_scmd *cmd, t_buin *buin)
{
	if (!cmd)
		return (0);
	if (!cmd->cmd)
		return (0);
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
}

int	do_in_parent(t_scmd *cmd, t_buin *buin)
{
	t_pipe	pipe_data;
	int		open_file_status;

	open_file_status = apply_fd(cmd->file, &pipe_data);
	if (open_file_status != EXIT_SUCCESS)
		return (open_file_status);
	if (!cmd->cmd)
		return (EXIT_SUCCESS);
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
}
