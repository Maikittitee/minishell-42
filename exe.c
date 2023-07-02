/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/02 19:04:24 by ktunchar         ###   ########.fr       */
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

void	input_pipe(t_cmd **cmd, char *input, char **env)
{
	int	i;
	char **s;

	i = 0;
	s = ft_split(input, ' ');
	while (s[i])
	{
		if (!ft_strchr(s[i], '|'))
		{
			if (i == 0)
				create_cmd(cmd, new_cmd(s[i], env));
			else
				cmd_add(cmd, new_cmd(s[i], env));
		}
		i++;
	}
	ft_double_free(s);
	
}

void	fix_fd_for_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->fd->in = -1;
		cmd->fd->out = -1;
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_cmd	**cmd;
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

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd *));

	create_cmd(cmd, new_cmd("ls -l", env));
	// cmd_add(cmd, new_cmd("grep .c", env));
	// cmd_add(cmd, new_cmd("wc -l", env));
	print_cmd(cmd);
	// del_head(cmd);
	// print_cmd(cmd);
	do_pipe(cmd, env);
	
	clear_free_cmd(cmd);
	// get_cmd_path(*cmd, env);
	return(0);
}