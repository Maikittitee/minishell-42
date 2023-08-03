/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 21:15:11 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/03 21:01:55 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atol(const char *str, int *code)
{
	int					i;
	int					sign;
	long long			n;

	n = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' \
			|| str[i] == '\r' || str[i] == '\n' || str[i] == '\f')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = (n * 10) + (str[i++] - '0');
		if (n >= LLONG_MAX && sign > 0 || n > LLONG_MAX && sign < 0)
			return (0);
	}
	*code += n * sign;
	return (n);
}
