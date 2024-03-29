/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:15:38 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 21:05:46 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "exe/exe.h"
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <sys/errno.h>

# define HEREDOC_FILENAME "../.heredoc"

# define TRUE 1
# define FALSE 0

# define ES_ERROR 1
# define ES_SYNTAC_ERROR 258
# define ES_PERMIS_DENIED 126 //??
# define ES_CMD_NOT_FOUND 127
# define ES_SIGINT_PARENT 1
# define ES_SIGINT_CHILD 130
# define ES_SIGKILL 137
# define ES_SIGSTOP 145

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

typedef enum e_err
{
	KERNEL_ERR,
	NOFILE_ERR,
	NOCMD_ERR,
	NOPERMISSION_ERR,
}	t_err;

typedef struct s_cmd
{
	char			**arg;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_line
{
	int	fd_in;
	int	fd_out;
}	t_line;

typedef struct s_pipe
{
	char	**path;
	char	**env;
	int		**fd;
	int		*pid;
	int		pcnt;
	int		npipe;
	int		nprocess;
	int		fd_in;
	int		fd_out;
}	t_pipe;

typedef struct s_fd
{
	int	*fd;
	int	nfile;
	int	correct_fd;
}	t_fd;

typedef enum e_buin
{
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_env,
	e_exit,
}	t_buin;

typedef enum e_rdir
{
	none,
	infile,
	outfile,
	append,
	heredoc,
}	t_rdir;

typedef enum e_type
{
	is_none,
	is_pipe,
	is_arg,
	is_rdir,
	is_file,
}	t_type;

enum e_define
{
	PIPE = '|',
	INDIR = '<',
	OUTDIR = '>',
	ENV_VAR = '$',
	SQUOTE = '\'',
	DQUOTE = '\"',
};

typedef struct s_token
{
	t_type			type;
	char			*content;
	int				len;
	int				quote;
	int				dollar;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char	*filename;
	t_rdir	type;
	int		index;
}	t_file;

typedef struct s_scmd
{
	char			**cmd;
	t_file			*file;
	struct s_scmd	*next;
}	t_scmd;

typedef struct s_shell
{
	t_token			*token;
	t_scmd			*scmd;
}	t_shell;

typedef struct s_global
{
	t_dict	**env_dict;
	t_shell	*shell_ptr;
	char	**env_ptr;
	int		return_code;
}	t_global;

t_global	g_global_data;

void	ft_clear_shell(t_shell *shell, int end);
// lexer //
int		valid_quote(char *s, int *qoute, int *dollar);
int		valid_token(t_token *token);
void	trim_quote(t_token **token);
// parser //
// utils //
int		ft_isspace(char c);
int		ft_isrdir(char c);
int		ft_isquote(char c);
int		ft_isarg(char c);

// skip_operator.c //
int		skip_rdir(char *s);
int		skip_qoute(char *s, char c, int *dollar);
int		skip_arg(char *s, int *qoute, int *dollar);

// token.c
t_token	*create_token(char *content, int qoute, int dollar, int len);
void	classify_add_token(t_token **lst, t_token *new);
t_token	*last_token(t_token *lst);
void	clear_token(t_token **lst);
void	ft_init_shell(t_shell *shell, char **env);

// scmd.c and scmd2.c //
t_scmd	*create_scmd(t_token **token);
void	ft_add_scmd(t_scmd **lst, t_scmd *new);
void	clear_scmd(t_scmd **lst);
void	main_handler(int signum);
void	exec_handler(int signum);
bool	set_signal(void);
void	free_2d(char **s);
char	**get_cmd(char **cmd, char *content);
t_scmd	*last_scmd(t_scmd *lst);
t_rdir	rdir_type(char *content);
void	get_file(t_file *file, char *rdir, char *filename);
int		count_rdir(t_token *token);

// exe //

char	**get_paths(char **env);
void	ft_double_free(char **s);
int		cmdsize(t_scmd *cmd);
int		do_fork(t_scmd *cmd, t_pipe pipe_data);
int		do_pipe(t_scmd *cmd);
int		ft_heredoc(char *start, char *eof);
int		do_here(t_file *in_here);
int		count_file_by_type(t_file *file, t_rdir type);
int		count_file(t_file *file);
void	ft_free_file(t_file *file);
int		ft_max(int *fd, int size);
int		apply_fd(t_file *file, t_pipe *pipe_data);
int		strstrlen(char **s);
int		join_path(t_scmd *cmd, char **paths);
char	**get_paths(char **env);
int		do_built_in(t_scmd *cmd, t_buin *buin);
int		is_built_in(char *cmd);
int		assign_buin(char *cmd, t_buin *buin);
char	**dup_env(char **env);
t_dict	**get_env_dict(char **env);
void	ft_free_dict(t_dict **dict);
char	*get_value2(t_dict **dict, char *target_str);
int		change_env(char *key, char *value);
int		add_new_env(char *new_env);
int		delete_env(char *key);
void	update_env_dict(void);
int		raise_error(char *msg, t_err mode);
int		ft_env(char **arg);
int		ft_pwd(char **arg);
int		ft_cd(char **arg);
int		ft_unset(char **arg);
int		ft_export(char **arg);
int		executor(t_scmd *cmd);
int		ft_exit(char **arg);
int		ft_echo(char **arg);
int		ft_isvar(char c);
int		ft_varlen2(char *s);
int		is_valid_var(char *s);
int		ft_strcmp2(const char *s1, const char *s2);
int		count_file_by_type(t_file *file, t_rdir type);
int		count_file(t_file *file);
int		strstrlen(char **s);
t_fd	get_fd_data(t_file *file);
int		change_env(char *key, char *value);
int		delete_env(char *key);
void	update_env_dict(void);
void	ft_child(t_scmd *cmd, t_pipe pipe_data, char **env);
int		is_do_in_parent(t_scmd *cmd, t_buin *buin);
int		do_in_parent(t_scmd *cmd, t_buin *buin);
void	close_pipe(t_pipe pipe_data);
void	wait_all(int *pid, t_pipe pipe_data, int *status);
void	ft_dup(int ifd, t_pipe piped, int fd_infile, int fd_outfile);
int		cmd_execute(t_scmd *cmd, t_pipe pipe_data);
void	expand_token(t_token **token);
int		ft_isvar(char c);
int		check_1stchar_var(char c);
int		ft_varlen(char *token);
int		break_input(char *line, t_token **token);
char	*ft_restr(char *re, char *token, char var_len, int *start);
void	parser(t_shell *shell);
int		is_exist(t_dict **dict, char *target_str);
int		replace_env(char *key, char *value);

#endif
