/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:25:28 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/02 22:35:49 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_type(t_type type)
{
	if (type == is_pipe)
		printf("\033[2;34m" "pipe" "\033[0m");
	else if (type == is_arg)
		printf("\033[2;34m" "arg" "\033[0m");
	else if (type == is_rdir)
		printf("\033[2;34m" "rdir" "\033[0m");
	else if (type == is_file)
		printf("\033[2;34m" "file" "\033[0m");
}

void	print_token(t_token	*token)
{
	while (token)
	{
		printf("[ %s =", token->content);
		print_type(token->type);
		if (token->quote)
		{
			printf("\033[1;30m" ":" "\033[0m");
			printf("q=");
			printf("\033[2;35m" "%d" "\033[0m", token->quote);
		}
		if (token->dollar)
		{
			printf("\033[1;30m" ":" "\033[0m");
			printf("d=");
			printf("\033[2;35m" "%d" "\033[0m", token->dollar);
		}
		printf(" ]");
		token = token->next;
		if (token)
			printf("\033[2;31m" " -> " "\033[0m");
	}
	printf("\n");
}

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

void	print_rdir(t_scmd *scmd)
{
	int	i;
	int	j;
	char **tmp;

	j = 1;
	while (scmd)
	{
		i = 0;
		if (scmd->cmd)
		{
			tmp = scmd->cmd;
			printf("scmd%d = ", j++);
			while (*tmp)
				printf("\033[2;35m" "%s " "\033[0m", *(tmp)++);
			printf("\n");
		}

		if (scmd->file)
		{
			while (scmd->file[i].type)
			{
				printf("%s = ", scmd->file[i].filename);
				print_rdir_type(scmd->file[i].type);
				i++;
			}
		}
		else
		{
			printf("file = ");
			printf("\033[2;31m" "%s\n" "\033[0m", NULL);
		}
		printf("\n\n");
		scmd = scmd->next;
	}
	printf("scmd%d = ", j++);
	printf("END\n");
}

void	print_flow(t_shell *shell, t_flow flow, char *content)
{
	printf("\033[38;5;208m" "\n\n--------> %s PART <--------\n\n" "\033[0m", content);
	if (flow == f_token)
		print_token(shell->token);
	else
		print_rdir(shell->scmd);
	printf("\n\n");
}
void	print_myenv(void)
{
	int	i = 0;
	while (global_data.env_dict[i])
	{
		printf("%s", global_data.env_dict[i]->key);
		printf("=");
		printf("%s\n", global_data.env_dict[i]->value);
		i++;
	}
}

// void	print_form(t_scmd *scmd)
// {
// 	t_form	form;


// }