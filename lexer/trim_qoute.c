/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_qoute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:42:29 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/02 21:12:51 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	trim_quote(t_token **token)
{
	int		i;
	int		q;
	char	*trimed;
	char	*str;
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->quote)
		{
			i = 0;
			str = tmp->content;
			trimed = malloc(sizeof(char) * (ft_strlen(str) - (tmp->quote * 2) + 1));
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
			free(tmp->content);
			tmp->content = ft_strdup(trimed);
			free(trimed);
			tmp->quote--;
		}
		tmp = tmp->next;
	}
}
