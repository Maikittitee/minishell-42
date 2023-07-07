/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/06 18:04:32 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	is_pipe(char *input)
{
	while(*input)
	{
		if (*input == '|')
			return (1);
		input++;
	}
	return (0);
}

t_line	*init_line(t_file **in_here, t_file **out_append)
{
	t_line *line;
	
	line = malloc(sizeof(line));
	if (!line)
		perror("malloc failed.");
	
	line->fd_in = 0;
	line->fd_out = 1;
	line->in_here = in_here;
	line->out_append = out_append;
	line->cmd = NULL;
	line->cmd = malloc(sizeof(t_cmd *));
	if (!line->cmd)
		perror("malloc failed.");
	return (line);
	
	
}

t_file **create_file(void)
{
	t_file **ret;

	ret = malloc(sizeof(t_file *) * 4);
	ret[0] = malloc(sizeof(t_file));
	ret[0]->filename = ft_strdup("FakeInfile");
	ret[0]->index = 0;
	ret[0]->type = INFILE;
	
	ret[1] = malloc(sizeof(t_file));
	ret[1]->filename = ft_strdup("Here_rai");
	ret[1]->index = 1;
	ret[1]->type = HEREDOC;
	
	ret[2] = malloc(sizeof(t_file));
	ret[2]->filename = ft_strdup("REAL_INFILE");
	ret[2]->index = 2;
	ret[2]->type = INFILE;

	ret[3] = NULL;

	return (ret);
}


t_file **create_file2(void)
{
	t_file **ret;

	ret = malloc(sizeof(t_file *) * 3);
	ret[0] = malloc(sizeof(t_file));
	ret[0]->filename = ft_strdup("THISAPPEND");
	ret[0]->index = 0;
	ret[0]->type = APPEND;
	
	ret[1] = malloc(sizeof(t_file));
	ret[1]->filename = ft_strdup("outfile");
	ret[1]->index = 1;
	ret[1]->type = OUTFILE;

	ret[2] = NULL;

	return (ret);
}

void	print_line(t_line *line)
{
	int	i;

	i = 0;

	printf("--- INFILE AND HEREDOC --- \n")	;
	while (line->in_here[i])
	{
		printf("index: %d filename: %s type: %d\n",line->in_here[i]->index, line->in_here[i]->filename, line->in_here[i]->type);
		i++;	
	}
	i = 0;
	printf("--- OUTFILE AND APPEND --- \n");
	while (line->out_append[i])
	{
		printf("index: %d filename: %s type: %d\n",line->out_append[i]->index, line->out_append[i]->filename, line->out_append[i]->type);
		i++;
	}
	printf("fd_in: %d\n", line->fd_in);
	printf("fd_out: %d\n", line->fd_out);
	print_cmd(line->cmd);
}

int	main(int ac, char **av, char **env)
{
	t_line	*line;
	t_cmd	**cmd;
	t_file	**indoc;
	t_file	**outapp;

	indoc = create_file();
	outapp = create_file2();
	

	(void)ac;
	(void)av;
	(void)env;

	cmd = NULL;
	// line = NULL;
	cmd = malloc(sizeof(t_cmd *));
	
	line = init_line(indoc, outapp);
	get_fd(line);
	cmd_create(cmd, new_cmd("ls -l", env));
	// cmd_add(cmd, new_cmd("grep .c", env));
	line->cmd = cmd;
	print_line(line);	
	// print_cmd(line->cmd);	
	// return (do_pipe(line, env));
	// ft_heredoc("EOF");
	usleep(1000000);
	// unlink(".here");
}