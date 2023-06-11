/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:09:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/12 00:10:36 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lib/libft/libft.h"

typedef	struct	s_cmd{ // link list of cmd
	char *cmd;
	char **arg;
	struct s_cmd *next; 
}t_cmd;

typedef struct	s_line{ // all line data seperate
	char *infile;
	char *outfile;
	char **env;
	t_cmd *cmd_data;
}t_line;


int	exe_cmd(t_cmd *cmd_d, char **env, char **paths);
char **get_paths(char **env);
// typedef	struct s_pipe_data{
// 	size_t	n_pipe;
// 	char *infile;
// 	char *outfile;
// 	char **env;
// 	t_cmd *cmd;
	

// }t_pipe_data;