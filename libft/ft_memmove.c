/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:09:07 by ksaelim           #+#    #+#             */
/*   Updated: 2022/04/05 23:11:38 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	i = -1;
	d = (char *)dst;
	s = (char *)src;
	if (!d && !s)
		return (NULL);
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	else
	{
		d += len;
		s += len;
		while (len > ++i)
			*--d = *--s;
	}
	return (dst);
}
