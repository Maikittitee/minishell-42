/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:17:25 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/24 16:56:41 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parser(t_shell *shell)
{
	t_token *tmp;

	tmp = shell->token;
	while (tmp)
		ft_add_scmd(&shell->scmd, create_scmd(&tmp));
}

int check_1stchar_var(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

char *ft_restr(char *re, char *token, char var_len, int *start)
{
	char *new;
	int re_len;
	int i;
	int j;

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
	printf("end_new: %d\n", *start);
	free(token);
	return (new);
}

char *get_return_code(char *token, int *start)
{
	char *code;

	code = ft_itoa(global_data.return_code);
	if (!code)
		return (NULL);
	token = ft_restr(code, token, 2, start);
	if (!token)
		return (NULL);
	free(code);
	return (token);
}

int ft_isvar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

char *ft_get_var(char *token)
{
	int i;

	i = 0;
	while (global_data.env_dict[i])
	{
		// printf("%s\n", global_data.env_dict[i]->key);
		if (!ft_strcmp(global_data.env_dict[i]->key, token))
		{
			printf("stop\n");
			printf("get_correct: %s\n", global_data.env_dict[i]->value);
			return (ft_strdup(global_data.env_dict[i]->value));
		}
		i++;
	}
	return (NULL);
}

char *get_value(char *token, int *start, int var_len)
{
	char *var;
	char *correct_var;

	var = ft_strndup(&token[*start + 1], var_len - 1);
	printf("var: %s\n", var);
	correct_var = ft_get_var(var);
	printf("correct_var: %s\n", correct_var);
	free(var);
	token = ft_restr(correct_var, token, var_len, start);
	if (!token)
		return (NULL);
	// *start += ft_strlen(correct_var) + 1;
	free(correct_var);
	printf("uuuuu\n");
	return (token);
}

int ft_varlen(char *token)
{
	int i;

	i = 0;
	if (check_1stchar_var(token[i]))
		i++;
	while (ft_isvar(token[i]))
		i++;
	return (i);
}

char *ft_expander(char **token, int *start)
{
	char c;

	c = token[0][*start + 1];
	if (c == '?')
		*token = get_return_code(*token, start);
	else if (check_1stchar_var(c))
	{
		printf("here\n");
		printf("var_len: %d\n", ft_varlen(&token[0][*start + 1]) + 1);
		*token = get_value(*token, start, ft_varlen(&token[0][*start + 1]) + 1);
		printf("why: %s\n", *token);
	}
	else
		(*start)++;
	return (*token);
}

void expand_token(t_token **token)
{
	t_token *tmp;
	int is_dq;
	int i;

	is_dq = 0;
	tmp = *token;
	while (tmp)
	{
		i = 0;
		printf("========\n");
			printf("%s\n", tmp->content);
		while (tmp->content[i] && tmp->dollar)
		{
			printf("i: %d\n", i);
			if (tmp->content[i] == '$')
			{
				printf("1\n");
				// exit(0);
				tmp->content = ft_expander(&tmp->content, &i);
				tmp->dollar--;
			}
			else if (tmp->content[i] == SQUOTE && !is_dq)
			{
				printf("3\n");
				printf("see:----> %c\n", tmp->content[i]);
				printf("%s\n", &tmp->content[i]);
				i += skip_qoute(&tmp->content[i], tmp->content[i], NULL);
			}
			else if (tmp->content[i++] == DQUOTE)
			{
				printf("2\n");
				is_dq = (is_dq + 1) % 2;
			}
		}
		tmp = tmp->next;
	}
}

int break_input(char *line, t_token **token, int qoute, int dollar)
{
	int len;
	char *str;
	char *tmp;

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
			return (free(tmp), FALSE);
		ft_strlcpy(str, line, len + 1);
		classify_add_token(token, create_token(str, &qoute, &dollar, len));
		line += len;
	}
	return (free(tmp), TRUE);
}

void ft_clear_shell(t_shell *shell, int end)
{
	if (!end)
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
	}
}

int ft_manager(t_shell *shell, char **env)
{
	if (!break_input(shell->line, &shell->token, 0, 0))
	{
		ft_clear_shell(shell, FALSE);
		return (FALSE);
	}
	if (!valid_token(shell->token))
	{
		ft_clear_shell(shell, FALSE);
		return (FALSE);
	}
	// if (!expand_token())
	// 	return (FALSE);
	// if (!trim_quote())
	// return (FALSE);
	// if (!parser())
	// 	return (0);
	// if (!executor())
	// 	return (0);
	print_token(shell->token);
	printf("\n\n");
	expand_token(&shell->token);
	trim_quote(&shell->token);
	print_token(shell->token);
	printf("\n\n");
	parser(shell);
	print_rdir(shell->scmd);
	printf("\n\n");
	// (void)env;
	executor(shell->scmd, env);
	printf("success\n");
	printf("return code: %d\n", global_data.return_code);
	// free(shell->line);
	return (TRUE);
}

char *handling_arg(char *arg)
{
	char *handle;
	int i;

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

void ft_init_shell(t_shell *shell, char **env, char **av)
{
	(void)av;
	env = dup_env(env);
	global_data.env_dict = get_env_dict(env);
	shell->scmd = NULL;
	shell->token = NULL;
}

int main(int ac, char **av, char **env)
{
	char *arg;
	t_shell shell;

	if (ac != 1)
		return (0);
	ft_init_shell(&shell, env, av);
	// int	i = 0;
	// while (global_data.env_dict[i])
	// {
	// 	printf("%s", global_data.env_dict[i]->key);
	// 	printf("=");
	// 	printf("%s\n", global_data.env_dict[i]->value);
	// 	i++;
	// }
	// exit(0);
	while (1)
	{
		arg = readline("minishell $");
		if (!arg)
			break;
		add_history(arg);
		shell.line = handling_arg(arg);
		if (!shell.line)
			continue;
		if (!ft_manager(&shell, env))
			continue;
		// printf("hello it meeee\n");
		ft_clear_shell(&shell, FALSE);
	}
	printf("exit\n");
	ft_double_free(env);
	ft_free_dict(global_data.env_dict);
	// ft_clear_shell(&shell, TRUE);
	return (0);
}