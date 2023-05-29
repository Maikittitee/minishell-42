/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:28:05 by maikittitee       #+#    #+#             */
/*   Updated: 2023/02/28 14:23:17 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//EXE		./pipex infile cmd1 cmd2 outfile
//ARG		   0	  1		2	 3		4
//fd[0] is for read from the pipe
//fd[1] is for write to the  pipe

#include "pipex.h"

void	ft_displayerr(int err, char *msg, int errnum, t_pipex *pipex)
{
	if (err == ARG_ERR)
		ft_putstr_fd("Invalid number of argument.\n", 2);
	else if (err == FORK_ERR)
		perror("Fork error :");
	else if (err == PIPE_ERR)
		perror("Pipe error :");
	else if (err == FILE_ERR)
		msg = ft_strjoin(msg, ": no such file or directory\n");
	else if (err == CMD_ERR)
		msg = ft_strjoin(msg, ": command not found\n");
	if (msg && (err == FILE_ERR || err == CMD_ERR))
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	if (pipex)
		ft_free_pipex(pipex);
	exit (errnum);
}

void	ft_child1_process(t_pipex *pipex, char **av, char **env, int fd[2])
{
	int	infile_fd;

	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd < 0)
		ft_displayerr(FILE_ERR, av[1], EXIT_FAILURE, pipex);
	if (!pipex->access_flag1)
		ft_displayerr(CMD_ERR, av[3], 127, pipex);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(infile_fd);
	if (execve((pipex->cmd1)[0], pipex->cmd1, env) == -1)
		exit(errno);
}

void	ft_child2_process(t_pipex *pipex, char **av, char **env, int fd[2])
{
	int	outfile_fd;

	outfile_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd < 0)
		ft_displayerr(FILE_ERR, av[4], EXIT_FAILURE, pipex);
	if (!pipex->access_flag2)
		ft_displayerr(CMD_ERR, av[3], 127, pipex);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfile_fd);
	if (execve((pipex->cmd2)[0], pipex->cmd2, env) == -1)
		exit(errno);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	t_pipex	pipex;

	init_pipex(&pipex, env);
	if (ac != 5)
		ft_displayerr(ARG_ERR, NULL, 1, &pipex);
	ft_find_cmd(&pipex, av);
	if (pipe(fd) != 0)
		ft_displayerr(PIPE_ERR, NULL, errno, &pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		ft_displayerr(FORK_ERR, NULL, errno, &pipex);
	if (pipex.pid1 == 0)
		ft_child1_process(&pipex, av, env, fd);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		ft_displayerr(FORK_ERR, NULL, errno, &pipex);
	if (pipex.pid2 == 0)
		ft_child2_process(&pipex, av, env, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &(pipex.status), 0);
	ft_free_pipex(&pipex);
	return (WEXITSTATUS(pipex.status));
}
