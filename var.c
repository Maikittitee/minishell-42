/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 02:13:30 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/01 02:13:32 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exe.h"

int	ft_isvar(int c)
{
	if (c == '_' || ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_varlen(char *s)
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
		varlen = ft_varlen(s);
		if (s[varlen] == '\0' || s[varlen] == '=')
			return (1);
	}
	return (0);
		
}
