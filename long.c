#include <stdio.h>
#include <stdlib.h>

typedef enum e_rdir{
	none,
	infile,
	outfile,
	append,
	heredoc,
}	t_rdir;

typedef struct s_file
{
	char	*filename;
	t_rdir	type;
	// int		index;
}	t_file;

void	print_rdir_type(t_rdir type)
{
	if (type == infile)
		printf("\033[2;34m" "infile\n" "\033[0m");
	else if (type == outfile)
		printf("\033[2;34m" "outfile\n" "\033[0m");
	else if (type == heredoc)
		printf("\033[2;34m" "heredoc\n" "\033[0m");
	else if (type == append)
		printf("\033[2;34m" "append\n" "\033[0m");
}

int	main(void)
{
	t_file	*file;

	file = malloc(sizeof(t_file) * 4);
	file[0].filename = "file1";
	file[0].type = infile;
	file[1].filename = "file2";
	file[1].type = outfile;
	file[2].filename = "file3";
	file[2].type = append;
	file[3].type = none;

	while ((*file).type)
	{
		printf("%s\n", (*file).filename);
		print_rdir_type((*file).type);
		file++;
	}


}