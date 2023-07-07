/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:13:26 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/08 01:15:07 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	cmdsize(t_cmd *cmd)
{
	int	i;

	i = 0;
	while(cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	ft_free_line(t_line *line)
{
	// clear_free_cmd(line->cmd);
	ft_free_file(line->in_here);
	ft_free_file(line->out_append);
	free(line);
}