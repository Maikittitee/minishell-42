/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:50:20 by ksaelim           #+#    #+#             */
/*   Updated: 2022/08/04 14:58:30 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (*s1)
	{
		s3[i] = *(char *)s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		s3[i] = *(char *)s2;
		i++;
		s2++;
	}
	s3[i] = '\0';
	return (s3);
}
