/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:07:41 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/07 19:47:19 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	long	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}	
	return ((int)i);
}

char	*ft_itoa(int n)
{
	char	*buffer;
	int		len;

	len = ft_intlen(n);
	buffer = ft_calloc(len + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (n == 0)
		ft_memcpy(buffer, "0\0", 2);
	if (n == -2147483648)
	{
		ft_memcpy(buffer, "-2147483648\0", 12);
		n = 0;
	}
	if (n < 0)
	{
		buffer[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		buffer[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (buffer);
}

/*
int	main(void)
{
	
	printf("Test itoa\n");
	printf("-2147483648 = %s\n",ft_itoa(-2147483648));
	printf("0 = %s\n",ft_itoa(0));
	printf("-1 = %s\n",ft_itoa(-1));
	printf("12 = %s\n",ft_itoa(12));
	printf("5555 = %s\n",ft_itoa(5555));

	printf("--------------------------------\n");
	printf("Test intlen:\n");
	printf("-2147483648 = %d\n",ft_intlen(-2147483648));
	printf("12 = %d\n",ft_intlen(12));
	printf("45 = %d\n",ft_intlen(45));
	printf("123 = %d\n",ft_intlen(123));
	
}

*/