/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:15:11 by ksaelim           #+#    #+#             */
/*   Updated: 2022/10/16 10:09:36 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	n;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' \
			|| str[i] == '\r' || str[i] == '\n' || str[i] == '\f')
		i++;
	sign = 1;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = (n * 10) + (str[i++] - '0');
		if (n >= ULLONG_MAX && sign > 0)
			return (-1);
		if (n > ULLONG_MAX && sign < 0)
			return (0);
	}
	return (n * sign);
}
