/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 00:32:06 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 01:50:59 by ktunchar         ###   ########.fr       */
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

int	strstrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	count_file_by_type(t_file *file, t_rdir type)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!file)
		return (0);
	while (file[i].type != none)
	{
		if (file[i].type == type)
			cnt++;
		i++;
	}
	return (cnt);
}

int	count_file(t_file *file)
{
	int	i;

	i = 0;
	while (file[i].type != none)
		i++;
	return (i);
}
