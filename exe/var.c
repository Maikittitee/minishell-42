/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 02:13:30 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 00:13:20 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_varlen2(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '_' || ft_isalpha(s[i]))
		i++;
	else
		return (0);
	while (s[i] && ft_isvar(s[i]))
		i++;
	return (i);
}

int	is_valid_var(char *s)
{
	int	varlen;

	if (!s)
		return (0);
	if (s[0] == '_' || ft_isalpha(s[0]))
	{
		varlen = ft_varlen2(s);
		if (s[varlen] == '\0' || s[varlen] == '=')
			return (1);
	}
	return (0);
}
