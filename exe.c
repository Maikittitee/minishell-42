/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/28 02:41:53 by ktunchar         ###   ########.fr       */
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
	env = dup_env(env);
	global_data.env_dict = get_env_dict(env);
	global_data.env_ptr = env;	
	cmd = init_cmd(new_node("env"));
	// link_cmd(cmd, new_node("wc -l"));
	// link_cmd(cmd, new_node(""));
	print_cmd(cmd);
	executor(*cmd, env);
		
	printf(GRN"\nexit code is %d\n"RESET, global_data.return_code);
	ft_double_free(env);
	ft_free_dict(global_data.env_dict);
	clear_free_cmd(*cmd);
	free(cmd);
	return (global_data.return_code);	
}