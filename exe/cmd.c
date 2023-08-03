/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 00:24:58 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 01:45:41 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	join_path(t_scmd *cmd, char **paths)
{
	char	*check;
	char	*temp;
	int		i;

	i = 0;
	if (!cmd || !paths)
		return (0);
	if (!cmd->cmd[0][0])
		return (0);
	if (access(cmd->cmd[0], F_OK) == EXIT_SUCCESS)
		return (1);
	check = ft_strjoin(paths[i], cmd->cmd[0]);
	while (paths[i] && access(check, F_OK) != EXIT_SUCCESS)
	{
		i++;
		free(check);
		check = ft_strjoin(paths[i], cmd->cmd[0]);
	}
	if (paths[i] == NULL)
		return (free(check), 0);
	temp = cmd->cmd[0];
	cmd->cmd[0] = ft_strdup(check);
	return (free(check), free(temp), 1);
}
