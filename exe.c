/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/18 00:46:56 by ktunchar         ###   ########.fr       */
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
	// ret[0] = malloc(sizeof(t_file));
	// ret[0]->filename = ft_strdup("infile");
	// ret[0]->index = 0;
	// ret[0]->type = INFILE;
	
	ret[0] = malloc(sizeof(t_file));
	ret[0]->filename = ft_strdup("eof");
	ret[0]->index = 0;
	ret[0]->type = HEREDOC;
	
	ret[1] = malloc(sizeof(t_file));
	ret[1]->filename = ft_strdup("infile");
	ret[1]->index = 1;
	ret[1]->type = INFILE;
	
	ret[2] = malloc(sizeof(t_file));
	ret[2]->filename = ft_strdup("outfile");
	ret[2]->index = 2;
	ret[2]->type = OUTFILE;
	ret[3] = NULL;


	return (ret);
}


void	print_file(t_file **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		printf("%d.%s[%d]\n", i + 1, file[i]->filename, file[i]->type);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_line *line;
	t_cmd	**cmd;
	t_file	**file;
	
	(void)ac;
	(void)av;
	env = dup_env(env);
	line = init_line();
	global_data.env_dict = get_env_dict(env);
	// file = create_file();
	file = NULL;
	if (apply_fd(line, file) == -1)
		return (EXIT_FAILURE);
	// print_file(file);
	printf("the file infile_fd is %d\n", line->fd_in);
	printf("the file outfile_fd is %d\n", line->fd_out);
	
	

	cmd = malloc(sizeof(t_cmd *));
	cmd_create(cmd, new_cmd("ls -l", env));
	cmd_add(cmd, new_cmd("wc -l", env));
	do_pipe(line, cmd, env);
	
	// ft_double_free(env);
	// ft_free_dict(global_data.env_dict);
	// ft_free_file(file);
	// clear_free_cmd(cmd);
	return (1);	
	// return (do_pipe(line, cmd, env));
}