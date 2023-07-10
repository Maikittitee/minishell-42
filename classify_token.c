/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:38:09 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/10 16:44:02 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	get_type(char token, t_type pre_type)
{
	if (token == PIPE)
		return (t_pipe);
	else if (ft_isrdir(token))
		return (t_rdir);
	else if (pre_type == t_rdir)
		return (t_filename);
	else
		return (t_arg);
}

int	classify_token(t_token *token)
{
	int	i;

	i = 0;
	token->type = malloc(sizeof(t_type) * token->n_token);
	if (!token->type)
		return (0);
	while (i < token->n_token)
	{
		if (i == 0)
			token->type[i] = get_type(token->value[i], t_none);
		else
			token->type[i] = get_type(token->value[i], token->type[i - 1]);
		if (token->type[i] == t_pipe)
			token->n_pipe++;
		i++;
	}
	return (1);
}
