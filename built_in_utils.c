/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:09:21 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/14 00:43:53 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	is_built_in(char *cmd, t_buin *buin)
{
	if (!cmd)
		return (0);
	
	// if (ft_strncmp(cmd, "echo", 4) == 0)
	// 	return (*buin = e_echo, 1);
	// else if (ft_strncmp(cmd, "cd", 2) == 0)
	// 	return (*buin = e_cd, 1);
	// if (ft_strncmp(cmd, "pwd", 3) == 0)
	// {
		printf("jing mai\n");
		*buin = e_pwd;
		return (1);
	// }
	// else if (ft_strncmp(cmd, "export", 6) == 0)
	// 	return (*buin = e_export, 1);
	// else if (ft_strncmp(cmd, "unset", 5) == 0)
	// 	return (*buin = e_unset, 1);
	// else if (ft_strncmp(cmd, "env", 3) == 0)
	// 	return (*buin = e_env, 1);
	// else if (ft_strncmp(cmd, "exit", 4) == 0)
	// 	return (*buin = e_exit, 1);
	// else
	// 	return (0);
}

int	do_built_in(t_cmd *cmd, t_buin *buin)
{
	int	status;

	status = 888;	
	if (*buin == e_pwd)
		status = ft_pwd(cmd->arg);
	// else if (buin == e_echo)
	// 	status = ft_echo(cmd->arg);
	// else if (buin == e_cd)
	// 	status = ft_cd(cmd->arg);
	// else if (buin == e_export)
	// 	status = ft_export(cmd->arg);
	// else if (buin == e_unset)
	// 	status = ft_unset(cmd->arg);
	// else if (buin == e_env)
	// 	status = ft_env(cmd->arg);
	// else if (buin == e_exit)
	// 	status = ft_exit(cmd->arg);
	return (status);
}
