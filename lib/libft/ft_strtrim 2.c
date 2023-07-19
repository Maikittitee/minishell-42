/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:47:52 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/22 16:55:29 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isinset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*buffer;
	char	*str;
	int		front;
	int		back;
	int		i;

	if (!s1)
		return (NULL);
	str = (char *)s1;
	front = 0;
	back = ft_strlen(str) - 1;
	while (ft_isinset(str[front], (char *)set))
		front++;
	while (ft_isinset(str[back], (char *)set) && back > front)
		back--;
	buffer = malloc((back - front + 2) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (front <= back)
		buffer[i++] = str[front++];
	buffer[i] = '\0';
	return (buffer);
}
/*
int	main(void)
{
	printf(">>%s<<\n",ft_strtrim("lorem ipsum dolor sit amet","te"));
}
*/