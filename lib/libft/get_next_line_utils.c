/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:49:14 by ktunchar          #+#    #+#             */
/*   Updated: 2023/03/26 01:19:49 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i] != (char)c && str[i])
		i++;
	if (str[i] == (char)c)
		return (str + i);
	if (c == '\0')
		return (str);
	else
		return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char		*buffer;
	int			i;
	int			j;
	static int	count;

	count++;
	if (!s2)
		return (NULL);
	buffer = malloc((ft_strlen_mode(s1, 0) + ft_strlen_mode(s2, 0) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[j])
			buffer[i++] = s1[j++];
	j = 0;
	while (s2[j])
	{
		buffer[i++] = s2[j++];
	}
	buffer[i] = '\0';
	if (s1)
		free (s1);
	return (buffer);
}

size_t	ft_strlen_mode(const char *s, int mode)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (mode == 1 && s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strdup_nl(const char *s1)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(sizeof(char) * ft_strlen_mode(s1, 1) + 2);
	if (!buffer)
		return (NULL);
	while (s1[i])
	{
		buffer[i] = s1[i];
		if (s1[i] == '\n')
			break ;
		i++;
	}
	i++;
	buffer[i] = '\0';
	return (buffer);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(sizeof(char) * ft_strlen_mode(s1, 0) + 2);
	if (!buffer)
		return (NULL);
	while (s1[i] != '\0')
	{
		buffer[i] = s1[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
