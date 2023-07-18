/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 23:24:19 by ksaelim           #+#    #+#             */
/*   Updated: 2022/03/25 23:59:47 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ss;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	ss = (char *)malloc(ft_strlen(s) + 1);
	if (!ss)
		return (0);
	while (s[i])
	{
		ss[i] = (*f)(i, s[i]);
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
