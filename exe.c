/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/21 01:52:02 by ktunchar         ###   ########.fr       */
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
	global_data.return_code = do_pipe(cmd, env);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_scmd **cmd;
	
	(void)ac;
	(void)av;
	env = dup_env(env);
	global_data.env_dict = get_env_dict(env);
	
	cmd = init_cmd(new_node("cat exe.h"));
	link_cmd(cmd, new_node("grep int"));
	link_cmd(cmd, new_node("wc -l"));
	print_cmd(cmd);
	executor(*cmd, env);
		
	ft_double_free(env);
	ft_free_dict(global_data.env_dict);
	clear_free_cmd(*cmd);
	free(cmd);
	return (global_data.return_code);	
}