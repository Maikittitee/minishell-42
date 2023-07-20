/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:09:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/21 02:17:41 by ktunchar         ###   ########.fr       */
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

typedef	enum e_rdir{
	none,
	infile,
	outfile,
	append,
	heredoc
} t_rdir;

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
	t_rdir type;
	int	index;
	struct s_file *next;

} t_file;

typedef	struct s_line{
	int			fd_in;
	int			fd_out;
}	t_line;

typedef	struct s_pipe{
	char **env;
	int	**fd;
	int	npipe;
	int	nprocess;
	int	fd_in;
	int	fd_out;
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

typedef struct s_scmd
{
    char **cmd;
    t_file *file;
    struct s_scmd *next;
}    t_scmd;




#define NOFILE_ERR 1
#define NOPERMISSION_ERR 2
#define CMD_ERR 3
#define TOO_MUCH_ARG 4

t_scmd **init_cmd(t_scmd *cmd);
t_scmd *new_node(char *str);
void	link_cmd(t_scmd **head, t_scmd *cmd);

char	**get_paths(char **env);
void	print_cmd(t_scmd **head);
void	clear_free_cmd(t_scmd *cmd);
void	ft_double_free(char **s);
int		cmdsize(t_scmd *cmd);
int		do_fork(t_scmd *cmd, t_pipe pipe_data, int *status, char **env);
int		do_pipe(t_scmd *cmd, char **env);
int		ft_heredoc(char *start, char *eof);
int		do_here(t_file *in_here);
int		count_file_by_type(t_file *file, t_rdir type);
int		count_file(t_file *file);
void	ft_free_file(t_file *file);
int		ft_max(int *fd, int size);
int		check_fd_in(t_file *file);
int		apply_fd(t_file *file, t_pipe *pipe_data);
int		strstrlen(char **s);
int		join_path(t_scmd *cmd, char **paths);
char	**get_paths(char **env);
int		do_built_in(t_scmd *cmd, t_buin *buin);
int		is_built_in(char *cmd, t_buin *buin);
char 	**dup_env(char **env);
t_dict 	**get_env_dict(char **env);
void	ft_free_dict(t_dict **dict);
char 	*dict_get_by_key(t_dict **dict, char *target_str);

int	raise_error(char *msg, int mode);

int		ft_env(char **arg);
int		ft_pwd(char **arg);

#endif