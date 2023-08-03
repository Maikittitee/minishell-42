/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:15:43 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 02:22:26 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	do_start(char *start, int fd)
{
	char	*buffer;

	if (!start)
		return ;
	while (start)
	{
		write(STDOUT_FILENO, ">", 1);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buffer, start, ft_strlen(start)) == 0)
		{
			free(buffer);
			break ;
		}
		free(buffer);
	}
}

int	ft_heredoc(char *start, char *eof)
{
	int		here_fd;
	char	*buffer;

	here_fd = open(HEREDOC_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0777);
	do_start(start, here_fd);
	while (eof)
	{
		write(STDOUT_FILENO, ">", 1);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buffer, eof, ft_strlen(eof)) == 0)
		{
			free(buffer);
			break ;
		}
		write(here_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	if (start)
		free(start);
	if (eof)
		free(eof);
	close(here_fd);
	return (open(HEREDOC_FILENAME, O_RDONLY));
}

t_file	*get_here_doc(t_file *file)
{
	t_file	*here;
	int		nhere;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nhere = count_file_by_type(file, heredoc);
	if (nhere == 0)
		return (NULL);
	here = malloc(sizeof(t_file) * (nhere + 1));
	while (file[i].type != none)
	{
		if (file[i].type == heredoc)
		{
			here[j].filename = file[i].filename;
			here[j].type = file[i].type;
			here[j].index = file[i].index;
			j++;
		}
		i++ ;
	}
	here[j].type = none;
	return (here);
}

int	do_here(t_file *file)
{
	char	*start;
	char	*end;
	t_file	*heredoc;
	int		nheredoc;

	heredoc = get_here_doc(file);
	if (heredoc == NULL)
		return (-1);
	nheredoc = count_file(heredoc);
	if (nheredoc == 1)
		start = NULL;
	else
		start = ft_strdup(heredoc[nheredoc - 2].filename);
	end = ft_strdup(heredoc[nheredoc - 1].filename);
	ft_free_file(heredoc);
	return (ft_heredoc(start, end));
}
