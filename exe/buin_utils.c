/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:09:21 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 00:24:53 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	assign_buin(char *cmd, t_buin *buin)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
	{
		return (*buin = e_echo, 1);
	}
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (*buin = e_cd, 1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (*buin = e_pwd, 1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (*buin = e_export, 1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (*buin = e_unset, 1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (*buin = e_env, 1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (*buin = e_exit, 1);
	else
	{
		return (0);
	}
}

int	is_built_in(char *cmd)
{
	if (!cmd)
		return (0);
	if (!*cmd)
	{
		return (0);
	}
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

int	do_built_in(t_scmd *cmd, t_buin *buin)
{
	if (*buin == e_pwd)
		exit(ft_pwd(cmd->cmd));
	else if (*buin == e_echo)
		exit(ft_echo(cmd->cmd));
	else if (*buin == e_cd)
		exit(ft_cd(cmd->cmd));
	else if (*buin == e_export)
		exit(ft_export(cmd->cmd));
	else if (*buin == e_unset)
		exit(ft_unset(cmd->cmd));
	else if (*buin == e_env)
		exit(ft_env(cmd->cmd));
	else if (*buin == e_exit)
		exit(ft_exit(cmd->cmd));
	else
		exit(0);
}
