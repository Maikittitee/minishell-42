/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:13:26 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/12 23:31:20 by ktunchar         ###   ########.fr       */
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
