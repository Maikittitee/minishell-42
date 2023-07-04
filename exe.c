/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/04 21:08:25 by ktunchar         ###   ########.fr       */
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
	line->fd_out = 1;
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
	line = init_line("cantread nofile chmod000 infile", "cantwrite cantread existfile outfile", NULL, NULL);
	apply_fd(line);
	cmd_create(cmd, new_cmd("k", env));
	// cmd_add(cmd, new_cmd("grep .c", env));
	line->cmd = cmd;	
	print_cmd(line->cmd);	
	return (do_pipe(line, env));
}