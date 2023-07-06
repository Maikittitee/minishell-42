/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:33:10 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/06 17:53:07 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	strstrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	count_file(t_file **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	return (i);
}

// void	raise_error(char *msg, int mode)
// {
	
	
// }

int	open_promax(char *filemame, int	type)
{
	
	
}

void	check_fd(t_file **file, int	*fd)
{
	
	int	i;

	i = 0;
	while(file[i])
	{
		
		
	}
}

void	get_fd(t_line *line)
{
	// int	i;
	int	*in_fd;

	// i = 0;
	if (line->in_here != NULL)
	{
		in_fd = malloc(sizeof(int) * count_file(line->in_here)); 
		check_fd(line->in_here, in_fd);
	}
	
	// while ()
	
}