/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 00:31:34 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 00:31:35 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_double_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i])
			free(s[i]);
		i++;
	}
	free(s);
}

void	free_cmd(t_scmd *cmd)
{
	if (!cmd)
		return ;
	ft_double_free(cmd->cmd);
	free(cmd);
}

void	clear_free_cmd(t_scmd *cmd)
{
	t_scmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = tmp->next;
		free_cmd(cmd);
		cmd = tmp;
	}
}
