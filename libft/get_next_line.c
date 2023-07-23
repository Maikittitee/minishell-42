/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:08:41 by ktunchar          #+#    #+#             */
/*   Updated: 2023/03/26 01:15:37 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO >> Check protect

#include "get_next_line.h"

void	*ft_memset_gnl(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (str);
}

char	*cut_line(char	*str)
{
	int		len_nl;
	int		len;
	char	*temp;

	len_nl = ft_strlen_mode(str, 1);
	len = ft_strlen_mode(str, 0);
	if (len_nl < len - 1)
	{
		temp = str;
		str = ft_strjoin_free(NULL, str + len_nl + 1);
		free(temp);
	}
	else
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_only_line(char *str)
{
	char	*line;

	if (ft_strchr_gnl(str, '\n'))
		line = ft_strdup_nl(str);
	else
		line = ft_strdup_gnl(str);
	return (line);
}

char	*read_line(int fd, char *str)
{
	int		can_read;
	char	*buffer;

	can_read = 8000;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (can_read)
	{
		ft_memset_gnl(buffer, 0, BUFFER_SIZE + 1);
		can_read = read(fd, buffer, BUFFER_SIZE);
		if (can_read <= 0)
			break ;
		str = ft_strjoin_free(str, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	line = NULL;
	str = read_line(fd, str);
	if (str)
	{
		line = get_only_line(str);
		str = cut_line(str);
	}
	return (line);
}

// int	main()
// {
// 	int	fd;

// //	char *a = "012345\nab";

// 	fd = open("gnlTester/files/41_no_nl",O_RDONLY);

// 	//printf("strlen_nl = %zu\n",ft_strlen_nl(a));
// 	//printf("strlen = %zu\n",ft_strlen(a));
// 	printf("line 1:%s|",get_next_line(fd));
// 	// printf("line 2:%s|",get_next_line(fd));
// 	// printf("line 3 : %s",get_next_line(fd));
// 	// printf("line 4 : %s",get_next_line(fd));
// }
