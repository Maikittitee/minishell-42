/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 00:32:06 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 00:34:51 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	ft_free_file(t_file *file)
{
	int	i;

	i = 0;
	if (!file)
		return ;
	while (file[i].type != none)
	{
		if (file[i].filename)
			free(file[i].filename);
		i++;
	}
	if (file)
		free(file);
}

int	ft_max(int *fd, int size)
{
	int	i;
	int	max;

	i = 0;
	if (!fd)
		return (-1);
	max = fd[0];
	while (i < size)
	{
		if (fd[i] > max)
			max = fd[i];
		i++;
	}
	return (max);
}
