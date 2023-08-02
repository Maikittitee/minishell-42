/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:38:06 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/02 15:40:48 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	raise_error(char *msg, t_err mode)
{
	int	ret;

	ret = 0;
	if (mode == KERNEL_ERR)
	{
		perror(msg);
		return (1);
	}
	else if (mode == NOFILE_ERR)
	{
		msg = ft_strjoin(msg, ": No such file or directory\n");
		ret = 1;
	}
	else if (mode == NOCMD_ERR)
	{
		msg = ft_strjoin(msg, ": command not found\n");
		ret = 127;
	}
	else if (mode == NOPERMISSION_ERR)
	{
		msg = ft_strjoin(msg, ": Permission denied\n");
		ret = 126;
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
	return (ret);
}