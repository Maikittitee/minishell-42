/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 20:00:50 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/08 16:31:27 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	buffer = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof (char));
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	while (s1[j])
		buffer[i++] = s1[j++];
	j = 0;
	while (s2[j])
		buffer[i++] = s2[j++];
	return (buffer);
}
/*
int	main(void)
{
	printf ("%s",ft_strjoin("Hello","World"));
}
*/
