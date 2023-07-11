/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:09:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/11 18:51:21 by ktunchar         ###   ########.fr       */
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

enum e_type
{
	HEREDOC,
	INFILE,
	APPEND,
	OUTFILE
};

#define HEREDOC_FILENAME ".heredoc"

typedef struct s_global{
	int	return_code;
	char **env;
} t_global;

typedef struct s_cmd{
	char			**arg;
	struct s_cmd	*next;
}	t_cmd;


typedef	struct s_file{
	char *filename;
	int	type;
	int	index;
	
} t_file;

typedef	struct s_line{
	int			fd_in;
	int			fd_out;
}	t_line;

typedef	struct s_pipe{
	int	**fd;
	int	npipe;
	int	nprocess;
	
}t_pipe;

#define NOFILE_ERR 1
#define NOPERMISSION_ERR 2
#define CMD_ERR 3


int		exe_cmd(t_cmd *cmd_d, char **env, char **paths);
int		get_cmd_path(t_cmd *cmd_d, char **env);
char	**get_paths(char **env);
t_cmd	*new_cmd(char *arg, char **env);
int		cmd_create(t_cmd **head, t_cmd *new_cmd);
int		cmd_add(t_cmd **head, t_cmd *new_cmd);
void	print_cmd(t_cmd **head);
void	clear_free_cmd(t_cmd **cmd);
void	ft_double_free(char **s);
// void	del_head(t_cmd **cmd);
// int		execute(t_cmd *cmd, char **env);
// int		executes(t_cmd **cmd, char **env);
int		cmdsize(t_cmd *cmd);
void	do_fork(t_cmd **cmd, t_line *line, t_pipe pipe_data, int *status, char **env);
int	do_pipe(t_line *line, t_cmd **cmd, char **env);
int	ft_heredoc(char *start, char *eof);
int	get_fd(t_line *line);
int	count_file_by_type(t_file **file, int type);
int	count_file(t_file **file);
int	do_here(t_file **in_here);
void	ft_free_file(t_file **file);
void	ft_free_line(t_line *line);
int	ft_max(int *fd, int size);
int	check_fd_in(t_file **file);
int	check_fd_out(t_file **file);


#endif