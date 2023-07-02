/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/02 22:49:38 by ktunchar         ###   ########.fr       */
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
	line->infile = ft_split(infile, ' ');
	line->outfile = ft_split(outfile, ' ');
	line->heredoc = ft_split(heredoc, ' ');
	line->append = ft_split(append, ' ');
	line->fd_in = 0;
	line->fd_in = 1;
	line->cmd = malloc(sizeof(t_cmd *));
	return (line);
	
	
}

int	main(int ac, char **av, char **env)
{
	t_line	*line;
	// char	*input;

	(void)ac;
	(void)av;

	// while (1)
	// {
	// 	input = readline(GRN"mainishell $ "RESET);
	// 	if (ft_strncmp(input, "exit", 4) == 0)
	// 	{
	// 		free(input);
	// 		break;
	// 	}
	// 	cmd = malloc(sizeof(t_cmd *));
	// 	if (is_pipe(input))
	// 	{
	// 		input_pipe(cmd, input, env);
	// 		fix_fd_for_pipe(*cmd);
	// 		do_pipe(cmd, env);
	// 	}
	// 	else
	// 	{
	// 		create_cmd(cmd, new_cmd(input, env));
	// 		executes(cmd, env);
	// 	}
	// 	free(input);
	// }
	line = init_line(NULL, NULL, NULL, NULL);
	if (new_line(line, new_cmd("ls -l", env)))
	{
		dprintf(1,"here\n");
	}
	// cmd_add(cmd, new_cmd("grep .c", env));
	// cmd_add(cmd, new_cmd("wc -l", env));
	dprintf(2, "OK\n");
	// print_line(line);
	
	dprintf(2, "OK2\n");
	// del_head(cmd);
	// print_cmd(cmd);
	do_pipe(line, env);
	
	// clear_free_cmd(cmd);
	// get_cmd_path(*cmd, env);
	return(0);
}