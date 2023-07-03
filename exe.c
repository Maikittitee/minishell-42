/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/03 17:56:40 by ktunchar         ###   ########.fr       */
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

// void	input_pipe(t_cmd **cmd, char *input, char **env)
// {
// 	int	i;
// 	char **s;

// 	i = 0;
// 	s = ft_split(input, ' ');
// 	while (s[i])
// 	{
// 		if (!ft_strchr(s[i], '|'))
// 		{
// 			if (i == 0)
// 				create_cmd(cmd, new_cmd(s[i], env));
// 			else
// 				cmd_add(cmd, new_cmd(s[i], env));
// 		}
// 		i++;
// 	}
// 	ft_double_free(s);
	
// }

t_line	*init_line(char *infile, char *outfile, char *heredoc, char *append)
{
	t_line *line;
	
	line = malloc(sizeof(line));
	if (!line)
		perror("malloc failed.");
	line->infile = ft_split(infile, ' ');
	line->outfile = ft_split(outfile, ' ');
	line->heredoc = ft_split(heredoc, ' ');
	line->append = ft_split(append, ' ');
	line->fd_in = 0;
	line->fd_in = 1;
	line->cmd = NULL;
	line->cmd = malloc(sizeof(t_cmd *));
	if (!line->cmd)
		perror("malloc failed.");
	return (line);
	
	
}

int	main(int ac, char **av, char **env)
{
	t_line	*line;
	t_cmd	**cmd;

	(void)ac;
	(void)av;
	(void)env;

	cmd = NULL;
	// line = NULL;
	cmd = malloc(sizeof(t_cmd *));
	line = init_line("infile", "outfile", NULL, NULL);
	cmd_create(cmd, new_cmd("ls -l", env));
	cmd_add(cmd, new_cmd("grep .c", env));
	cmd_add(cmd, new_cmd("wc -l", env));
	line->cmd = cmd;	
	// line = malloc(sizeof(line));
	// cmd = NULL;
	// line->cmd = &new; //ok
	// printf("")

	print_cmd(line->cmd);
	printf("ending");
	
	// del_head(cmd);
	// print_cmd(cmd);
	// do_pipe(line, env);
	
	// clear_free_cmd(cmd);
	// ft_double_free(line->infile);
	// ft_double_free(line->outfile);
	// ft_double_free(line->heredoc);
	// ft_double_free(line->append);
	// // free(line->cmd);
	// free(line);
	// get_cmd_path(*cmd, env);
	return(0);
}