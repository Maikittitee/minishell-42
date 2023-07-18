/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:17:25 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/18 15:14:01 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_initshell(t_shell *shell)
// {}



void	parser(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	while (tmp)
		ft_add_scmd(&shell->scmd, create_scmd(&tmp));
}

// void	expand_token(t_token **token)
// {
// 	t_token	*tmp;
// 	char	*str;

// 	tmp = *token;
// 	while (tmp)
// 	{
// 		if (tmp->dollar)
// 		{
// 			str = tmp->content;
// 			if (tmp->quote)
// 			{
// 				while (*str)
// 				{

// 				}
// 			}
// 			else
// 			{}
// 			while (*str)
// 			{
// 				if (*str == '$')
// 				str++;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

int	break_input(char *line, t_token **token, int qoute, int dollar)
{
	int		len;
	char	*str;
	char	*tmp;

	tmp = line;
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		len = valid_quote(line, &qoute, &dollar);
		if (!len)
			return (free(tmp), FALSE);
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return (FALSE);
		ft_strlcpy(str, line, len + 1);
		classify_add_token(token, create_token(str, &qoute, &dollar, len));
		line += len;
	}
	return (free(tmp), TRUE);
}


void	ft_clear_shell(t_shell *shell, int	end)
{
	if (!end)
	{
		clear_token(&shell->token);
		clear_scmd(&shell->scmd);
	}
}

int	ft_manager(t_shell *shell)
{
	if (!break_input(shell->line, &shell->token, 0, 0))
		return (FALSE);
	if (!valid_token(shell->token))
		return (FALSE);
	// if (!expand_token())
	// 	return (FALSE);
	// if (!trim_quote())
		// return (FALSE);
	// if (!parser())
	// 	return (0);
	// if (!executor())
	// 	return (0);
	trim_quote(&shell->token);
	print_token(shell->token);
	printf("\n\n");
	parser(shell);
	print_rdir(shell->scmd);
	// free(shell->line);
	ft_clear_shell(shell, FALSE);
	return (TRUE);
}

char	*handling_arg(char *arg)
{
	char	*handle;
	int	i;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (!arg[i])
	{
		free(arg);
		return (NULL);
	}
	handle = ft_strtrim(arg, " \t");
	if (!ft_strlen(handle))
	{
		free(arg);
		return (NULL);
	}
	free(arg);
	return (handle);
}


int	main(void)
{
	char	*arg;
	t_shell	shell;

	// ft_init_shell();
	while (1)
	{
		arg = readline("minishell $");
		if (!arg)
			break ;
		add_history(arg);
		shell.line = handling_arg(arg);
		if (!shell.line)
			continue;
		if (!ft_manager(&shell))
			ft_clear_shell(&shell, FALSE);
	}
	printf("exit\n");
	// ft_clear_shell(&shell, TRUE);
	return (0);
}