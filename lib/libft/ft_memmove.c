/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:57:40 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/22 17:03:47 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		sign = -1;
		i = (int)len - 1;
	}
	while (len > 0)
	{
		((char *)dst)[i] = ((char *)src)[i];
		len --;
		i += (sign * 1);
	}
	return (dst);
}
