/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 23:36:12 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/11 22:05:17 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*buffer;
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	buffer = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (str[i])
	{
		buffer[i] = f(i, str[i]);
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

/*
char func (unsigned int i, char *str) {
	return (*(str - 'a'));
}

ft_strmapi("Hello, world", func);
*/