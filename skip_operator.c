/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:54:56 by ksaelim           #+#    #+#             */
/*   Updated: 2023/06/26 12:59:36 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_qoute(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
		return (0);
	return (i + 1);
}

int	skip_rdir(char *s)
{
	int i;

	i = 1;
	if (s[i] == INRDIR || s[i] == OUTRDIR)
        i++;
    if (ft_isrdir(s[i]))
        return (0);
	return (i);
}