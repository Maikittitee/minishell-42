/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:56 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:02:01 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_valid_token(char *content)
{
	printf("syntax error near unexpected token `%s'\n", content);
	g_global_data.return_code = 258;
	return (FALSE);
}

int	valid_token(t_token *token)
{
	t_type	type;
	t_token	*next;

	if (token->type == is_pipe)
		return (print_valid_token(token->content));
	while (token)
	{
		type = token->type;
		next = token->next;
		if (next)
		{
			if (next && type == is_pipe && next->type == is_pipe)
				return (print_valid_token(next->content));
			else if (next && type == is_rdir && (next->type == is_pipe || \
				next->type == is_rdir))
				return (print_valid_token(next->content));
		}
		else
		{
			if (type == is_pipe || type == is_rdir)
				return (print_valid_token("newline"));
		}
		token = next;
	}
	return (TRUE);
}
