/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_qoute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:42:29 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/02 17:51:01 by ktunchar         ###   ########.fr       */
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
			printf("size of trimed %lu\n", ft_strlen(str) - (tmp->quote * 2) + 1);
			printf("bp1\n");
			while (*str)
			{
				if (*str && ft_isquote(*str))
				{
					q = skip_qoute(str, *str, NULL) - 2;
					str++;
					while (q)
					{
						trimed[i] = *(str);
						printf("q:%d><%c\n",q, *str);
						str++;
						i++;
						q--;
					}
					str++;
				}
				else
					trimed[i++] = *(str)++;
			}
			printf("bp2\n");
			trimed[i] = '\0';
			free(tmp->content);
			tmp->content = ft_strdup(trimed);
			free(trimed);
			tmp->quote--;
		}
		tmp = tmp->next;
	}
}
