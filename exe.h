/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:09:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/16 03:54:50 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"

typedef struct s_fd{
	int	in;
	int	out;
}	t_fd;

typedef struct s_cmd{
	char			**arg;
	char			**file;
	t_fd			*fd;
	struct s_cmd	*next;
}	t_cmd;

int		exe_cmd(t_cmd *cmd_d, char **env, char **paths);
int		get_cmd_path(t_cmd *cmd_d, char **env);
char	**get_paths(char **env);
t_cmd	*new_cmd(char *arg, char **env);
int		create_cmd(t_cmd **head, t_cmd *new_cmd);
int		cmd_add(t_cmd **head, t_cmd *new_cmd);
void	print_cmd(t_cmd **head);

#endif