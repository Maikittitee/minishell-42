/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:33:10 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/11 18:06:37 by ktunchar         ###   ########.fr       */
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

int	check_fd_in(t_file **file)
{
	int	i;
	int	j;
	int	*fd;

	j = 0;
	i = 0;
	if (file == NULL)
		return (0);
	fd = malloc(sizeof(int) * count_file(file));
	if (count_file_by_type(file, HEREDOC) != 0)
		fd[j] = do_here(file);
	else
		fd[j] = -1;
	j++;
	while (file[i])
	{
		if (file[i]->type == INFILE)
		{
			fd[j] = open(file[i]->filename, O_RDONLY);
			if (fd[j] == -1)
			{
				raise_error(file[i]->filename, NOFILE_ERR);
				free(fd);
				return (-1);
			}
		}
		else 
			fd[j] = -1;
		i ++;
		j ++;
	}
	return (ft_max(fd, count_file(file)));
}

int	check_fd_out(t_file **file)
{
	int	i;
	int	j;
	int	*fd;

	i = 0;
	j = 0;
	if (file == NULL)
		return (1);
	fd = malloc(sizeof(int) * count_file(file));
	while (file[i])
	{
		if (file[i]->type == APPEND)
		{
			printf("APPEND fd[%d]=%d\n", j, fd[j]);
			fd[j] = open(file[i]->filename, O_RDWR | O_CREAT | O_APPEND, 0777);
		}
		if (file[i]->type == OUTFILE)
		{
			printf("OUTFILE fd[%d]=%d\n", j, fd[j]);
			fd[j] = open(file[i]->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		}
		if (fd[j] == -1)
		{
			raise_error(file[i]->filename, NOPERMISSION_ERR);
			free(fd);
			return (-1);
		}
		i++;
		j++;
	}
	printf("this is max %d\n", ft_max(fd, count_file(file)));
	return (ft_max(fd, count_file(file)));
	
}

int	get_fd(t_line *line)
{
	

	
	printf("in get_fd1 line->out_append addr is %p\n", line->out_append);
	if (line->in_here != NULL)
	{
		if (check_fd_in(line->in_here) == -1)
		{
			// free(fd_input);
			return (-1);
		}
		// if heredoc is lastone ? { line->fd_in = fd[0];}
		// else {line->fd_in = ft_max(fd);}	
	}
	printf("in get_fd2 line->out_append addr is %p\n", line->out_append);
	if (line->out_append != NULL)
	{
		line->fd_out = check_fd_out(line->out_append);
		if (line->fd_out == -1)
			return (-1);
	}
	else
		printf("no outfile\n");
	return (1);
}
