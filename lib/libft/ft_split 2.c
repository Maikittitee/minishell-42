/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:18:48 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/22 16:57:17 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_len(char *s, char c)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*append_word(char *s, char c)
{
	char	*buffer;
	size_t	i;
	size_t	j;
	size_t	len;

	len = word_len(s, c);
	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] != c)
			buffer[j++] = s[i];
		i++;
	}
	buffer[j] = '\0';
	return (buffer);
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}	
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	str = (char *)s;
	buffer = malloc(sizeof(char *) * (count_word(str, c) + 1));
	if (!buffer)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			buffer[j++] = append_word(&str[i], c);
		while (str[i] && str[i] != c)
			i++;
	}
	buffer[j] = NULL;
	return (buffer);
}

/*
int	main()
{
	int	i;
	char **dst;

	dst = ft_split("lorem ipsum dolor sit amet", ' ');
	
	//printf("%d\n",word_len("   hello",' '));
	
	i = 0;
	while (i < 13)
	{
		printf("index %d is %s\n",i,dst[i]);
		i++;
	}
}
*/
