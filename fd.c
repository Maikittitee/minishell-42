/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:33:10 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/12 23:56:55 by ktunchar         ###   ########.fr       */
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
	// int	i;
	// int	j;
	// t_fd fd_data;

	// j = 0;
	// i = 0;
	if (file == NULL)
		return (0);
	// fd_data.nfile = count_file_by_type(file, INFILE) + count_file_by_type(file, HEREDOC);
	// fd_data.fd = ft_calloc(sizeof(int), fd_data.nfile);
	return (do_here(file));
}

int	check_fd_out(t_file **file)
{
	int	i;
	int	j;
	t_fd fd_data;

	i = 0;
	j = 0;
	if (file == NULL)
		return (1);
	fd_data.nfile = count_file_by_type(file, APPEND) + count_file_by_type(file, OUTFILE);
	if (fd_data.nfile == 0)
		return (1);
	fd_data.fd = ft_calloc(sizeof(int), fd_data.nfile);
	while (file[i])
	{
		if (file[i]->type == APPEND) ///////////// 
		{
			fd_data.fd[j] = open(file[i]->filename, O_RDWR | O_CREAT | O_APPEND, 0777);
			j++;
		}
		else if (file[i]->type == OUTFILE)
		{
			fd_data.fd[j] = open(file[i]->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
			j++;
		}
		if (fd_data.fd[j] == -1) 
		{
			raise_error(file[i]->filename, NOPERMISSION_ERR);
			free(fd_data.fd);
			return (-1);
		} ////////////////////////////////////////// -> Can Make it as function
		i++;
	}
	fd_data.correct_fd = ft_max(fd_data.fd, fd_data.nfile); /// optimize
	printf("this is fd out %d\n", fd_data.correct_fd);
	free(fd_data.fd);
	return (fd_data.correct_fd);
	
}

int	apply_fd(t_line *line, t_file **file)
{
	line->fd_in = check_fd_in(file);
	line->fd_out = check_fd_out(file);
	
	if (line->fd_out < 0 || line->fd_in < 0)
		return (-1);
	return (1);
		
}
