/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:22:39 by ksaelim           #+#    #+#             */
/*   Updated: 2022/03/16 00:58:32 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_intlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*n1;
	int		len;
	int		i;

	nbr = n;
	i = 0;
	len = ft_intlen(nbr) - 1;
	n1 = malloc(sizeof(char) * (ft_intlen(nbr) + 1));
	if (!n1)
		return (NULL);
	if (nbr < 0)
	{
		n1[i++] = '-';
		nbr *= -1;
	}
	while (i <= len)
	{
		n1[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	n1[ft_intlen(n)] = '\0';
	return (n1);
}
