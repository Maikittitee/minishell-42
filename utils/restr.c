/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 04:29:57 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:30:27 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
