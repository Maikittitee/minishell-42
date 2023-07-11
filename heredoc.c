/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:15:43 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/11 17:53:46 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_heredoc(char *start, char *eof) // return fd;
{
	int	here_fd;
	char *buffer;

	here_fd = open(HEREDOC_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (here_fd == -1)
		write(2, "here_fd ERROR\n", 14);
	while (start)
	{
		write(STDOUT_FILENO, ">", 1);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buffer, start, ft_strlen(eof)) == 0)
		{
			free(buffer);
			break;
		}
		free(buffer);
	}
	while (eof)
	{
		write(STDOUT_FILENO, ">", 1);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buffer, eof, ft_strlen(eof)) == 0)
		{
			free(buffer);
			break;
		}
		write(here_fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	if (start)
		free(start);
	if (eof)
		free(eof);
	return (here_fd);
}


t_file **get_here_doc(t_file **in_here)
{
	int	nhere;
	t_file **here;
	int	i;
	int	j;

	i = 0;
	j = 0;
	nhere = count_file_by_type(in_here, HEREDOC);
	here = malloc(sizeof(t_file *) * (nhere + 1));
	while (in_here[i])
	{
		if (in_here[i]->type == HEREDOC)
		{
			here[j] = malloc(sizeof(t_file));
			here[j]->filename = in_here[i]->filename;
			here[j]->type = in_here[i]->type;
			here[j]->index = in_here[i]->index;
			j++;
		}
		i++ ;
	}
	return (here);
	
	
}

int	do_here(t_file **in_here)
{
	char	*start;
	char	*end;
	t_file	**heredoc;
	int		nheredoc;
	heredoc = get_here_doc(in_here); 
	nheredoc = count_file(heredoc);
	if (nheredoc != 1)
		return (-1);
	if (nheredoc == 1)
		start = NULL;
	else
		start = ft_strdup(heredoc[nheredoc - 2]->filename);
	end = ft_strdup(heredoc[nheredoc - 1]->filename);
	ft_free_file(heredoc);
	return (ft_heredoc(start, end));
}