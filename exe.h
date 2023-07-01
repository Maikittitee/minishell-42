/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:09:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/02 00:31:39 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "colors.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"

typedef struct s_fd{
	int	in;
	int	out;
}	t_fd;

typedef struct s_cmd{
	char			**arg;
	char			**infile; 
	char			**outfile;
	char			**heredoc;
	char			**append;
	t_fd			*fd;
	struct s_cmd	*next;
}	t_cmd;

typedef	struct s_pipe{
	int	**fd;
	int	npipe;
	int	nprocess;
	
}t_pipe;

int		exe_cmd(t_cmd *cmd_d, char **env, char **paths);
int		get_cmd_path(t_cmd *cmd_d, char **env);
char	**get_paths(char **env);
t_cmd	*new_cmd(char *arg, char **env);
int		create_cmd(t_cmd **head, t_cmd *new_cmd);
int		cmd_add(t_cmd **head, t_cmd *new_cmd);
void	print_cmd(t_cmd **head);
void	clear_free_cmd(t_cmd **cmd);
void	ft_double_free(char **s);
void	del_head(t_cmd **cmd);
int		execute(t_cmd *cmd, char **env);
int		executes(t_cmd **cmd, char **env);
int		cmdsize(t_cmd *cmd);
void	do_fork(t_cmd **cmd, t_pipe pipe_data, int *status, char **env);
int	do_pipe(t_cmd **cmd, char **env);

#endif