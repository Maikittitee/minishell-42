/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:15:43 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/05 17:31:16 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_heredoc(char *eof) // return fd;
{
	int	here_fd;
	char *buffer;

	here_fd = open(".here", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (here_fd == -1)
		write(2, "here_fd ERROR\n", 14);
	while (1)
	{
		write(STDOUT_FILENO, ">", 1);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buffer, eof, ft_strlen(eof)) == 0)
		{
			free(buffer);
			break;
		}
		write(here_fd, buffer, ft_strlen(buffer));
	}
	return (here_fd);
	
}