/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:44:56 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/18 15:12:09 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_token(t_token *token)
{
	t_type	type;
	t_token	*next;

	if (token->type == is_pipe)
	{
		printf("syntax error near unexpected token `%s'\n", token->content);
		return (FALSE);
	}
	while (token)
	{
		type = token->type;
		next = token->next;
		if (next)
		{
			if (next && type == is_pipe && next->type == is_pipe)
			{
				printf("syntax error near unexpected token `%s'\n", next->content);
				return (FALSE);
			}
			else if (next && type == is_rdir && (next->type == is_pipe || next->type == is_rdir))
			{
				printf("syntax error near unexpected token `%s'\n", next->content);
				return (FALSE);
			}

		}
		else
		{
			if(type == is_pipe || type == is_rdir)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (FALSE);
			}
		}
		token = next;
	}
	return (TRUE);
}
