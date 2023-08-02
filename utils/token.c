/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:05:11 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/03 04:12:59 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *last_token(t_token *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_type token_type(char *content, t_type pre_type)
{
	if (content[0] == PIPE)
		return (is_pipe);
	else if (ft_isrdir(*content))
		return (is_rdir);
	else if (pre_type == is_rdir)
		return (is_file);
	else
		return (is_arg);
}

void classify_add_token(t_token **lst, t_token *new)
{
	t_token *back;

	if (lst)
	{
		if (!*lst)
		{
			new->type = token_type(new->content, is_none);
			*lst = new;
		}
		else
		{
			back = last_token(*lst);
			new->type = token_type(new->content, back->type);
			back->next = new;
		}
	}
}

t_token *create_token(char *content, int qoute, int dollar, int len)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->quote = qoute;
	new->dollar = dollar;
	new->len = len;
	new->next = NULL;
	return (new);
}

void clear_token(t_token **lst)
{
	t_token *tmp;

	if (!lst || !(*lst))
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->content)
		{
			free((*lst)->content);
		}
		if (*lst)
		{
			free(*lst);
		}
		*lst = tmp;
	}
}
