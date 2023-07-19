/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:01:16 by ktunchar          #+#    #+#             */
/*   Updated: 2023/03/26 01:16:06 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

char	*ft_strchr_gnl(const char *s, int c);
char	*get_next_line(int fd);
char	*ft_strjoin_free(char *s1, char *s2);
size_t	ft_strlen_mode(const char *s, int mode);
char	*ft_strdup_nl(const char *s1);
char	*ft_strdup_gnl(const char *s1);

#endif