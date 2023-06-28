/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:48:59 by ksaelim           #+#    #+#             */
/*   Updated: 2023/06/28 12:11:05 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_len(char **s)
{	
	int	len;

	len = 0;
	while (**s && **s == ' ')
		(*s)++;
	if (ft_isrdir(**s))
		len = skip_rdir(*s);
	else if (**s == '$')
		len = 1;
	else
	{
		while (s[0][len] && ft_isarg(s[0][len]))
		{
			if (ft_isquote(s[0][len]))
				len += skip_qoute(*s, **s);
			else
				len++;
		}
	}
	if (!len)
		return (0);
	return (len);
}

int	valid_arg(char *s)
{
	int n_token;
	int	valid;

	n_token = 0;
	while (*s)
	{
		valid = word_len(&s);
		if (!valid)
			return (0);
		n_token++;
		s += valid;
	}
	printf("yeahhhh\n");
	return (n_token);
}
