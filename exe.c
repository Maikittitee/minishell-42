/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/12 00:33:22 by ktunchar         ###   ########.fr       */
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
	t_line *line;
	t_cmd	*curr;
	t_cmd	*cmd2;

	line = malloc(sizeof(t_line));
	line->cmd_data = malloc(sizeof(t_cmd));

	line->infile = NULL;
	line->outfile = NULL;
	line->env = env;
	line->cmd_data->cmd = ft_strdup("ls");
	line->cmd_data->arg = malloc(sizeof(char *) * 4) ;
	line->cmd_data->arg[0] = ft_strdup("ls");
	line->cmd_data->arg[1] = ft_strdup("-l");
	line->cmd_data->arg[2] = ft_strdup("-a");
	line->cmd_data->arg[3] = NULL;
	line->cmd_data->next = NULL;

	// cmd2 = malloc(sizeof(t_cmd));
	// cmd2->cmd = ft_strdup("cat");
	// cmd2->arg = malloc(sizeof(char *));
	// cmd2->arg[0] = NULL;
	// cmd2->next = NULL;

	// line->cmd_data->next = cmd2;
	
	char **paths = get_paths(env);
	// curr = line->cmd_data;
	// while (curr)
	// {
	// 	printf("%s\n", curr->cmd);	
	// 	curr = curr->next;
	// }
	exe_cmd(line->cmd_data, env, paths);



	// FREEEEEEEEE 
	free(line->cmd_data->cmd);
	free(line->cmd_data->arg[0]);
	free(line->cmd_data->arg[1]);
	free(line->cmd_data->arg[2]);
	free(line->cmd_data->arg);
	free(line->cmd_data);
	free(line);
	int	i;
	
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	// exe_cmd(cmd2);
	

	

	// execve(line->cmd_data->cmd, line->cmd_data->arg, env);

	
	
}