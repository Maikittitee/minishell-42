/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:33:10 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 02:00:09 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	get_infile_index(t_file *file)
{
	int	i;
	int	target;

	i = 0;
	target = -1;
	if (!file)
		return (-1);
	while (file[i].type != none)
	{
		if (file[i].type == infile || file[i].type == heredoc)
			target = i;
		i++;
	}
	return (target);
}

int	check_infile(char *filename, int *fd, int j)
{
	if (access(filename, F_OK) != 0)
		return (raise_error(filename, NOFILE_ERR), free(fd), -1);
	if (access(filename, R_OK) != 0)
		return (raise_error(filename, NOPERMISSION_ERR), free(fd), -1);
	fd[j] = open(filename, O_RDONLY);
	if (fd[j] == -1)
		return (raise_error(filename, KERNEL_ERR), free(fd), -1);
	return (1);
}

int	check_fd_in(t_file *file, int i, int j)
{
	t_fd	fd_data;
	int		real_index;
	int		heredoc_fd;

	real_index = get_infile_index(file);
	if (real_index == -1)
		return (0);
	heredoc_fd = do_here(file);
	fd_data = get_fd_data(file);
	while (file[i].type != none)
	{
		if (file[i].type == infile)
		{
			if (check_infile(file[i].filename, fd_data.fd, j) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (file[real_index].type == heredoc)
		return (heredoc_fd);
	fd_data.correct_fd = ft_max(fd_data.fd, fd_data.nfile);
	free(fd_data.fd);
	return (fd_data.correct_fd);
}

int	check_fd_out(t_file *file, int i, int j)
{
	t_fd	fd_data;

	fd_data.nfile = count_file_by_type(file, 3) + count_file_by_type(file, 2);
	if (fd_data.nfile == 0)
		return (1);
	fd_data.fd = ft_calloc(sizeof(int), fd_data.nfile);
	while (file[i].type != none)
	{
		if (file[i].type == append || file[i].type == outfile)
		{
			if (access(file[i].filename, F_OK) == 0 && \
			access(file[i].filename, W_OK) != 0)
				return (raise_error(file[i].filename, \
				NOPERMISSION_ERR), free(fd_data.fd), -1);
			if (file[i].type == append)
				fd_data.fd[j++] = open(file[i].filename, 2 | 512 | 8, 0644);
			else if (file[i].type == outfile)
				fd_data.fd[j++] = open(file[i].filename, 2 | 512 | 1024, 0644);
			if (fd_data.fd[j] == -1)
				return (raise_error(file[i].filename, 0), free(fd_data.fd), -1);
		}
		i++;
	}
	fd_data.correct_fd = ft_max(fd_data.fd, fd_data.nfile);
	return (free(fd_data.fd), fd_data.correct_fd);
}

int	apply_fd(t_file *file, t_pipe *pipe_data)
{
	pipe_data->fd_in = check_fd_in(file, 0, 0);
	pipe_data->fd_out = check_fd_out(file, 0, 0);
	if (pipe_data->fd_out < 0 || pipe_data->fd_in < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
