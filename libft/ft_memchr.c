/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:18:43 by ksaelim           #+#    #+#             */
/*   Updated: 2023/06/24 22:20:33 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	i = -1;
	if (n < 1)
		return (NULL);
	str = (char *)s;
	while (++i < n)
	{
		if (str[i] == (char)c)
			return ((void *)(str + i));
	}
	return (NULL);
}
