/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 04:14:36 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:16:06 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_return_code(char *token, int *start)
{
	char	*code;

	code = ft_itoa(g_global_data.return_code);
	if (!code)
		return (NULL);
	token = ft_restr(code, token, 2, start);
	if (!token)
		return (NULL);
	free(code);
	return (token);
}

char	*ft_get_var(char *token)
{
	int	i;

	i = 0;
	while (g_global_data.env_dict[i])
	{
		if (!ft_strcmp(g_global_data.env_dict[i]->key, token))
			return (ft_strdup(g_global_data.env_dict[i]->value));
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
