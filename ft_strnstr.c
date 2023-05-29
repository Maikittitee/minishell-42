/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:39:33 by ktunchar          #+#    #+#             */
/*   Updated: 2023/02/28 14:52:16 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (len < 0)
		return (0);
	if (!(needle[i]))
		return ((char *)haystack);
	str = (char *)haystack;
	while (str[i] && i <= len)
	{
		while (str[i + j] == needle[j] && str[i + j] && i + j < len)
			j++;
		if (!needle[j])
			return (str + i);
		i++;
		j = 0;
	}
	return (0);
}
