/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:48:59 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/10 17:20:14 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_len(char *s)
{
	int	len;

	len = 0;
	if (ft_isrdir(*s) || *s == PIPE)
		len = skip_rdir(s);
	else if (*s == '$')
		len = 1;
	else
		len = skip_arg(s);
	if (len)
		return (len);
	return (0);
}

int	valid_arg(char *s, int *n_token)
{
	int	valid;

	valid = 0;
	while (*s)
	{
		while (*s && *s == ' ')
			s++;
		if (!(*s))
			return (*n_token);
		valid = word_len(s);
		if (!valid)
			return (0);
		s += valid;
		*n_token += 1;
	}
	return (*n_token);
}
