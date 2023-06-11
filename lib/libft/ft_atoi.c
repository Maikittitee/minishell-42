/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:47:42 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/22 17:20:51 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	else if (c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_issign(char c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				ngt;
	int				i;

	i = 0;
	result = 0;
	ngt = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] && ft_issign(str[i]))
	{
		if (str[i] == '-')
			ngt = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (ngt == -1 && result > 9223372036854775808ull)
		result = 0;
	else if (ngt == 1 && result > 9223372036854775807ull)
		result = -1;
	return (ngt * result);
}
