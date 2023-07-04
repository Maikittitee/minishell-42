/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:33:10 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/04 21:13:44 by ktunchar         ###   ########.fr       */
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

// void	raise_error(char *msg, int mode)
// {
	
	
// }

void	apply_fd(t_line *line)
{
	int	i;
	int	*in_fd;

	in_fd = malloc(sizeof(int) * strstrlen(line->infile));

	i = 0;
	while (line->infile[i])
	{
		in_fd[i] = open(line->infile[i], O_RDONLY);
		if (in_fd[i] == -1)
			return (raise_err(line->infile[i], FILE_ERR));
		i++;
	}
	return (1);
}