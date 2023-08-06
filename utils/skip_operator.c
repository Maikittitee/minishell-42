/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:54:56 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:02:01 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_qoute(char *s, char c, int *dollar)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '$' && dollar && c == DQUOTE)
			(*dollar)++;
		i++;
	}
	if (s[i] != c)
	{
		printf("syntax error unclosed double quote `%c'\n", c);
		g_global_data.return_code = 258;
		return (0);
	}
	return (i + 1);
}

int	skip_arg(char *s, int *qoute, int *dollar)
{
	int	i;
	int	q;

	i = 0;
	while (s[i] && ft_isarg(s[i]))
	{
		if (ft_isquote(s[i]))
		{
			q = skip_qoute(&s[i], s[i], dollar);
			if (!q)
				return (q);
			(*qoute)++;
			i += q;
		}
		else
		{
			if (s[i] == '$')
				(*dollar)++;
			i++;
		}
	}
	return (i);
}

int	skip_rdir(char *s)
{
	int	i;

	i = 1;
	if (s[i] == INDIR || s[i] == OUTDIR)
		i++;
	return (i);
}
