#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"

# define TRUE 1
# define FALSE 0

typedef enum e_rdir{
	none,
	infile,
	outfile,
	append,
	heredoc,
}	t_rdir;

typedef	enum e_type{
	is_none,
	is_pipe,
	is_arg,
	is_rdir,
	is_file,
}	t_type;

enum e_define{
	PIPE = '|',
	INDIR = '<',
	OUTDIR = '>',
	ENV_VAR = '$',
	SQUOTE = '\'',
	DQUOTE = '\"',
};

typedef struct s_line
{
	int	fd_in;
	int	fd_out;
}	t_line;

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
}	t_file;

typedef struct s_scmd
{
	char			**cmd;
	t_file			*file;
	struct s_scmd	*next;
}	t_scmd;

typedef struct s_shell
{
	t_token	*token;
	t_scmd	*scmd;
	char	*line;
}	t_shell;

// lexer //
int	valid_quote(char *s, int *qoute, int *dollar);
int	valid_token(t_token *token);
void	trim_quote(t_token **token);
// parser //
// utils //
int	ft_isspace(char c);
int ft_isrdir(char c);
int	ft_isquote(char c);
int	ft_isarg(char c);

// skip_operator.c //
int	skip_rdir(char *s);
int	skip_qoute(char *s, char c, int *dollar);
int	skip_arg(char *s, int *qoute, int *dollar);

// token.c
t_token	*create_token(char	*content, int *qoute, int *dollar, int len);
void	classify_add_token(t_token **lst, t_token *new);
t_token	*last_token(t_token *lst);
void	clear_token(t_token **lst);
void	ft_initshell(t_shell *shell);

// debug.c //
void	print_token(t_token	*token);
void	print_rdir(t_scmd *scmd);
void	print_rdir_type(t_rdir type);
void	print_type(t_type type);

// scmd.c //
t_scmd	*create_scmd(t_token **token);
void	ft_add_scmd(t_scmd **lst, t_scmd *new);
void	clear_scmd(t_scmd **lst);

#endif
