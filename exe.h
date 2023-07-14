/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:09:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/14 18:06:17 by ktunchar         ###   ########.fr       */
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

enum e_type
{
	HEREDOC,
	INFILE,
	APPEND,
	OUTFILE
};

#define HEREDOC_FILENAME ".heredoc"

typedef	struct s_dict{
	char	*key;
	char	*value;
}t_dict;

typedef struct s_global{
	int	return_code;
	t_dict	**env_dict;
	
} t_global;

t_global global_data;
// extern char **environ;

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

typedef struct s_fd{
	int	*fd;
	int	nfile;
	int correct_fd;
}t_fd;

typedef enum e_buin{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
}	t_buin;

#define NOFILE_ERR 1
#define NOPERMISSION_ERR 2
#define CMD_ERR 3
#define TOO_MUCH_ARG 4


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
int	count_file_by_type(t_file **file, int type);
int	count_file(t_file **file);
int	do_here(t_file **in_here);
void	ft_free_file(t_file **file);
int	ft_max(int *fd, int size);
int	check_fd_in(t_file **file);
int	apply_fd(t_line *line, t_file **file);
int	strstrlen(char **s);

void	raise_error(char *msg, int mode);
int	do_built_in(t_cmd *cmd, t_buin *buin);
int	is_built_in(char *cmd, t_buin *buin);
int	ft_pwd(char **arg);
char **dup_env(char **env);
t_dict **get_env_dict(char **env);
void	ft_free_dict(t_dict **dict);
char *printf("this is the value of $PWD: %s", dict_get_by_key(global_data.env_dict, "PWD"));(t_dict **dict, char *target_str);

#endif