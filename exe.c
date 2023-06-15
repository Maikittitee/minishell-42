/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/16 03:55:00 by ktunchar         ###   ########.fr       */
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

	(void)ac;
	(void)av;

	// cmd = NULL;
	cmd = malloc(sizeof(t_cmd *));

	create_cmd(cmd, new_cmd("ls -l", env));
	cmd_add(cmd, new_cmd("wc -l", env));
	print_cmd(cmd);
	// get_cmd_path(*cmd, env);
}