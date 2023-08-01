/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/01 19:54:20 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

t_file *create_file(void)
{
	t_file *ret;

	ret = malloc(sizeof(t_file) * 2);
	ret[0].filename = ft_strdup("eof");
	ret[0].index = 0;
	ret[0].type = heredoc;
	ret[1].type = none;
	return (ret);
}

int	executor(t_scmd *cmd, char **env)
{
	do_pipe(cmd, env);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_scmd **cmd;
	
	(void)ac;
	(void)av;
	global_data.env_ptr = dup_env(env);
	global_data.env_dict = get_env_dict(global_data.env_ptr);
	// global_data.env_ptr = env;	
	cmd = init_cmd(new_node("s"));
	link_cmd(cmd, new_node("wc -l"));
	// link_cmd(cmd, new_node(""));
	print_cmd(cmd);
	executor(*cmd, env);
	// int	i;

	// i = 0;
	// while (global_data.env_ptr[i])
	// {
	// 	printf("%s\n", global_data.env_ptr[i]);
	// 	i++;
	// }

	printf(GRN"\nexit code is %d\n"RESET, global_data.return_code);
	ft_double_free(global_data.env_ptr);
	ft_free_dict(global_data.env_dict);
	clear_free_cmd(*cmd);
	free(cmd);
	return (global_data.return_code);	
}