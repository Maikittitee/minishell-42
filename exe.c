/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/11 21:44:57 by ktunchar         ###   ########.fr       */
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

t_line	*init_line(void)
{
	t_line *line;
	
	line = malloc(sizeof(line));
	if (!line)
		perror("malloc failed.");
	
	line->fd_in = 0;
	line->fd_out = 1;
	return (line);
	
	
}

t_file **create_file(void)
{
	t_file **ret;

	ret = malloc(sizeof(t_file *) * 4);
	ret[0] = malloc(sizeof(t_file));
	ret[0]->filename = ft_strdup("fake_infile");
	ret[0]->index = 0;
	ret[0]->type = INFILE;
	
	ret[1] = malloc(sizeof(t_file));
	ret[1]->filename = ft_strdup("eof");
	ret[1]->index = 1;
	ret[1]->type = HEREDOC;
	
	ret[2] = malloc(sizeof(t_file));
	ret[2]->filename = ft_strdup("real_infile");
	ret[2]->index = 2;
	ret[2]->type = INFILE;

	ret[3] = NULL;

	return (ret);
}


int	main(int ac, char **av, char **env)
{
	t_line *line;
	t_cmd	**cmd;
	t_file	**file;

	
	(void)ac;
	(void)av;
	(void)env;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd *));
	line = init_line();
	printf("in main line addr is %p\n", line);
	apply_fd(line, file);
	
	
	
	printf("the file infile_fd is %d\n", line->fd_in);
	printf("the file outfile_fd is %d\n", line->fd_out);
	cmd_create(cmd, new_cmd("ls -l", env));
	cmd_add(cmd, new_cmd("grep .c", env));
	// print_cmd(cmd);

	// free(line->cmd);
	// clear_free_cmd(cmd);
	// ft_free_line(line);
	// unlink(HEREDOC_FILENAME);
	do_pipe(line, cmd, env);
	return (1);
}