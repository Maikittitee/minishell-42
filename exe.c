/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/14 18:04:22 by ktunchar         ###   ########.fr       */
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

	ret = malloc(sizeof(t_file *) * 3);
	// ret[0] = malloc(sizeof(t_file));
	// ret[0]->filename = ft_strdup("infile");
	// ret[0]->index = 0;
	// ret[0]->type = INFILE;
	
	ret[0] = malloc(sizeof(t_file));
	ret[0]->filename = ft_strdup("eof");
	ret[0]->index = 1;
	ret[0]->type = HEREDOC;
	
	ret[1] = malloc(sizeof(t_file));
	ret[1]->filename = ft_strdup("outfile");
	ret[1]->index = 2;
	ret[1]->type = OUTFILE;

	ret[2] = NULL;

	return (ret);
}


int	main(int ac, char **av, char **env)
{
	// t_line *line;
	// t_cmd	**cmd;
	// t_file	**file;
	
	(void)ac;
	(void)av;
	// (void)env;
	env = dup_env(env);
	global_data.env_dict = get_env_dict(env);

	printf("this is the value of $PWD: %s", dict_get_by_key(global_data.env_dict, "PWD"));

	ft_double_free(env);
	ft_free_dict(global_data.env_dict);

	// printf("sizeof(env)=%lu\n", sizeof(env));
	// cmd = NULL;
	// cmd = malloc(sizeof(t_cmd *));
	// line = init_line();
	// // file = create_file();
	// file = NULL;
	// printf("in main line addr is %p\n", line);
	// if (apply_fd(line, file) == -1)
	// 	return (EXIT_FAILURE);
	
	
	
	// printf("the file infile_fd is %d\n", line->fd_in);
	// printf("the file outfile_fd is %d\n", line->fd_out);
	// cmd_create(cmd, new_cmd("ls", env));
	// cmd_add(cmd, new_cmd("", env));
	return (1);	
	// return (do_pipe(line, cmd, env));
}