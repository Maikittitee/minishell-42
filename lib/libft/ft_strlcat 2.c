/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:51:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/04/27 20:23:25 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	initdstlen;

	if (dstsize > 0)
	{	
		i = 0;
		dstlen = ft_strlen(dst);
		initdstlen = dstlen;
		while (dstlen < dstsize - 1 && src[i])
		{
			dst[dstlen] = src[i];
			i++;
			dstlen++;
		}
		if (dstlen < dstsize)
			dst[dstlen] = '\0';
	}
	if ((!src || !dst) && dstsize == 0)
		return (0);
	if (ft_strlen(dst) < dstsize)
		return (ft_strlen(src) + initdstlen);
	else
		return (ft_strlen(src) + dstsize);
}
