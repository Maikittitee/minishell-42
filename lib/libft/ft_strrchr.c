/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:50:27 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/22 17:18:54 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*str;

	str = (char *)s;
	tmp = NULL;
	while (*str)
	{
		if (*str == (char)c)
			tmp = str;
		str++;
	}
	if (c == 0)
		return (str);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
