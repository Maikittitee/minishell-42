/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:17:25 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 00:21:04 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	while (tmp)
		ft_add_scmd(&shell->scmd, create_scmd(&tmp));
}

int	check_1stchar_var(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

char	*ft_restr(char *re, char *token, char var_len, int *start)
{
	char	*new;
	int		re_len;
	int		i;
	int		j;

	if (!re)
		re = "";
	re_len = ft_strlen(re);
	new = malloc(sizeof(char) * (ft_strlen(token) - var_len + re_len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < *start)
		new[i++] = token[j++];
	while (*re)
		new[i++] = *re++;
	j += var_len;
	while (token[j])
		new[i++] = token[j++];
	new[i] = '\0';
	*start += re_len;
	free(token);
	return (new);
}

char	*get_return_code(char *token, int *start)
{
	char	*code;

	code = ft_itoa(global_data.return_code);
	if (!code)
		return (NULL);
	token = ft_restr(code, token, 2, start);
	if (!token)
		return (NULL);
	free(code);
	return (token);
}

int	ft_isvar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

char	*ft_get_var(char *token)
{
	int	i;

	i = 0;
	while (global_data.env_dict[i])
	{
		if (!ft_strcmp(global_data.env_dict[i]->key, token))
			return (ft_strdup(global_data.env_dict[i]->value));
		i++;
	}
	return (NULL);
}

char	*get_value(char *token, int *start, int var_len)
{
	char	*var;
	char	*correct_var;

	var = ft_strndup(&token[*start + 1], var_len - 1);
	correct_var = ft_get_var(var);
	free(var);
	token = ft_restr(correct_var, token, var_len, start);
	if (!token)
		return (NULL);
	free(correct_var);
	return (token);
}

int	ft_varlen(char *token)
{
	int	i;

	i = 0;
	if (check_1stchar_var(token[i]))
		i++;
	while (ft_isvar(token[i]))
		i++;
	return (i);
}

char	*ft_expander(char **token, int *start)
{
	char	c;

	c = token[0][*start + 1];
	if (c == '?')
		*token = get_return_code(*token, start);
	else if (check_1stchar_var(c))
		*token = get_value(*token, start, ft_varlen(&token[0][*start + 1]) + 1);
	else
		(*start)++;
	return (*token);
}

void	expand_token(t_token **token)
{
	t_token	*tmp;
	int		is_dq;
	int		i;

	is_dq = 0;
	tmp = *token;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i] && tmp->dollar)
		{
			if (tmp->content[i] == '$')
			{
				tmp->content = ft_expander(&tmp->content, &i);
				tmp->dollar--;
			}
			else if (tmp->content[i] == SQUOTE && !is_dq)
				i += skip_qoute(&tmp->content[i], tmp->content[i], NULL);
			else if (tmp->content[i++] == DQUOTE)
				is_dq = (is_dq + 1) % 2;
		}
		tmp = tmp->next;
	}
}

int	break_input(char *line, t_token **token)
{
	int		len;
	int		qoute;
	int		dollar;
	char	*str;

	while (*line)
	{
		qoute = 0;
		dollar = 0;
		while (*line && *line == ' ')
			line++;
		len = valid_quote(line, &qoute, &dollar);
		if (!len)
			return (FALSE);
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return (FALSE);
		ft_strlcpy(str, line, len + 1);
		classify_add_token(token, create_token(str, qoute, dollar, len));
		line += len;
	}
	return (TRUE);
}

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
	global_data.return_code = 0;
	global_data.env_ptr = dup_env(env);
	global_data.env_dict = get_env_dict(env);
	global_data.shell_ptr = shell;
	shell->scmd = NULL;
	shell->token = NULL;
	set_termios(&shell->term);
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
		signal(SIGINT, &sigint_handler);
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
	restore_termios(&shell.term);
	ft_double_free(global_data.env_ptr);
	return (ft_free_dict(global_data.env_dict), printf("exit\n"), 0);
}
