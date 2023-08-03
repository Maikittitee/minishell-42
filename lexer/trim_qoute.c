/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_qoute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:42:29 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/03 22:27:06 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*trim_out(char *str, int quote)
{
	int		i;
	int		q;
	char	*trimed;
	char	*tmp;

	i = 0;
	tmp = str;
	trimed = malloc(sizeof(char) * (ft_strlen(str) - (quote * 2) + 1));
	while (*str)
	{
		if (*str && ft_isquote(*str))
		{
			q = skip_qoute(str, *str, NULL) - 2;
			str++;
			while (q--)
				trimed[i++] = *(str)++;
			str++;
		}
		else
			trimed[i++] = *(str)++;
	}
	trimed[i] = '\0';
	free(tmp);
	return (trimed);
}

void	trim_quote(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->quote)
			tmp->content = trim_out(tmp->content, tmp->quote);
		tmp = tmp->next;
	}
}
