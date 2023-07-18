/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:11:19 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/18 09:44:02 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dst;

	i = 0;
	while (s1[i] != '\0')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
	{
		dst[i] = s1[i];
	}
	dst[i] = '\0';
	return (dst);
}
