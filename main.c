/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:17:25 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 21:09:41 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_shell(t_shell *shell, int end)
{
	if (shell->token)
	{
		clear_token(&shell->token);
		shell->token = NULL;
	}
	if (shell->scmd)
	{
		clear_scmd(&shell->scmd);
		shell->scmd = NULL;
	}
	if (end)
		rl_clear_history();
}

int	ft_manager(char *line, t_shell *shell, char **env)
{
	(void)env;
	if (!break_input(line, &shell->token))
		return (FALSE);
	if (!valid_token(shell->token))
		return (FALSE);
	expand_token(&shell->token);
	trim_quote(&shell->token);
	parser(shell);
	executor(shell->scmd);
	ft_clear_shell(shell, FALSE);
	return (TRUE);
}

char	*handling_arg(char *arg)
{
	char	*handle;
	int		i;

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

void	ft_init_shell(t_shell *shell, char **env)
{
	g_global_data.return_code = 0;
	g_global_data.env_ptr = dup_env(env);
	g_global_data.env_dict = get_env_dict(env);
	g_global_data.shell_ptr = shell;
	shell->scmd = NULL;
	shell->token = NULL;
	set_signal();
}

int	main(int ac, char **av, char **env)
{
	char	*arg;
	t_shell	shell;

	if (ac != 1)
		return (printf("This Program Receive Only One Argument !\n"), 1);
	(void)av;
	ft_init_shell(&shell, env);
	while (1)
	{
		signal(SIGINT, &main_handler);
		arg = readline("minishell $");
		if (!arg)
			break ;
		add_history(arg);
		arg = handling_arg(arg);
		if (!arg)
			continue ;
		if (!ft_manager(arg, &shell, env))
			ft_clear_shell(&shell, FALSE);
		free(arg);
	}
	rl_clear_history();
	ft_double_free(g_global_data.env_ptr);
	return (ft_free_dict(g_global_data.env_dict), printf("exit\n"), 0);
}
