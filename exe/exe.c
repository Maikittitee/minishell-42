/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 21:14:19 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

t_fd	get_fd_data(t_file *file)
{
	t_fd	fd_data;

	fd_data.nfile = count_file_by_type(file, infile);
	fd_data.fd = ft_calloc(sizeof(int), fd_data.nfile);
	return (fd_data);
}

int	executor(t_scmd *cmd)
{
	do_pipe(cmd);
	return (1);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_scmd **cmd;

// 	(void)ac;
// 	(void)av;
// 	g_global_data.env_ptr = dup_env(env);
// 	g_global_data.env_dict = get_env_dict(g_global_data.env_ptr);
// 	// g_global_data.env_ptr = env;
// 	cmd = init_cmd(new_node("export"));
// 	// link_cmd(cmd, new_node("export"));
// 	// link_cmd(cmd, new_node(""));
// 	print_cmd(cmd);
// 	executor(*cmd, env);
// 	// int	i;

// 	// i = 0;
// 	// while (g_global_data.env_ptr[i])
// 	// {
// 	// 	printf("%s\n", g_global_data.env_ptr[i]);
// 	// 	i++;
// 	// }

// 	printf(GRN"\nexit code is %d\n"RESET, g_global_data.return_code);
// 	ft_double_free(g_global_data.env_ptr);
// 	ft_free_dict(g_global_data.env_dict);
// 	clear_free_cmd(*cmd);
// 	free(cmd);
// 	return (g_global_data.return_code);
// }