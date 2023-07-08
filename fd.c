/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:33:10 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/09 02:00:05 by ktunchar         ###   ########.fr       */
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

int	count_file_by_type(t_file **file, int type)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (file[i])
	{
		if (file[i]->type == type)
			cnt++;
		i++;
	}
	return (cnt);
}

int	count_file(t_file **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	return (i);
}

void	raise_error(char *msg, int mode)
{
	if (mode == NOFILE_ERR)
		msg = ft_strjoin(msg, ": No such file or directory");
	if (mode == NOPERMISSION_ERR)
		msg = ft_strjoin(msg, ": Permission denied");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

int	check_fd_in(t_file **file, int *fd)
{
	int	i;

	i = 0;
	if (count_file_by_type(file, HEREDOC) == 0)
		fd[i] = do_here(file);
	else
		fd[i] = -1;
	i++;
	while (file[i])
	{
		if (file[i]->type == INFILE)
		{
			fd[i] = open(file[i]->filename, O_RDONLY);
			if (fd[i] == -1)
			{
				raise_error(file[i]->filename, NOFILE_ERR);
				return (-1);
			}
		}
		else 
			fd[i] = -1;
		i++;
	}
	return (1);
}

int	check_fd_out(t_file **file)
{
	int	i;
	int	*fd;

	i = 0;
	fd = malloc(sizeof(int) * count_file(file));
	while (file[i])
	{
		if (file[i]->type == APPEND)
			fd[i] = open(file[i]->filename, O_RDWR | O_CREAT | O_APPEND);
		if (file[i]->type == OUTFILE)
			fd[i] = open(file[i]->filename, O_RDWR | O_CREAT | O_TRUNC);
		if (fd[i] == -1)
		{
			raise_error(file[i]->filename, NOPERMISSION_ERR);
			free(fd);
			return (-1);
		}
		i++;
	}
	return (ft_max(fd, count_file(file)));
	
}

int	get_fd(t_line *line)
{
	
	int	*fd_in;

	if (line->in_here != NULL)
	{
		fd_in = malloc(sizeof(int) * (count_file(line->in_here)));
		if (check_fd_in(line->in_here, fd_in) == -1)
		{
			free(fd_in);
			return (-1);
		}
		// if heredoc is lastone ? { line->fd_in = fd[0];}
		// else {line->fd_in = ft_max(fd);}	
		free(fd_in);
	}
	else
		line->fd_in = 0;
	if (line->out_append != NULL)
	{
		line->fd_out = check_fd_out(line->out_append);
		if (line->fd_out == -1)
			return (-1);
	}
	else
		line->fd_out = 1;
	return (1);
}
