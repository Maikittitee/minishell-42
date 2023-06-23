/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/23 18:42:18 by ktunchar         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_cmd	**cmd;
	char	*input;

	(void)ac;
	(void)av;

	while (1)
	{
		input = readline(GRN"mainishell $ "RESET);
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			free(input);
			return (0);
		}
		cmd = malloc(sizeof(t_cmd *));
		create_cmd(cmd, new_cmd(input, env));
		executes(cmd, env);
		free(input);
	}

	// cmd = NULL;
	cmd = malloc(sizeof(t_cmd *));

	// create_cmd(cmd, new_cmd("ls -l", env));
	// cmd_add(cmd, new_cmd("cat Makefile -e", env));
	// cmd_add(cmd, new_cmd("cat -e", env));
	// print_cmd(cmd);
	// del_head(cmd);
	// printf("after del\n");
	// print_cmd(cmd);
	// executes(cmd, env);
	
	// clear_free_cmd(cmd);
	// get_cmd_path(*cmd, env);
}