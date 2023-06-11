/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:13:36 by ktunchar          #+#    #+#             */
/*   Updated: 2022/09/04 22:13:38 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr_fd(-1 * 214748364, fd);
		ft_putchar_fd('8', fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-1 * n, fd);
	}
	else if (n <= 9)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

/*int	main()
{
	ft_putnbr_fd(2,1);
	printf("\n");
	ft_putnbr_fd(12,1);
	printf("\n");
	ft_putnbr_fd(-12,1);
	printf("\n");
	ft_putnbr_fd(-1232322,1);
	printf("\n");
	ft_putnbr_fd(0,1);
	printf("\n");
	ft_putnbr_fd('\0',1);
	printf("\n");
	ft_putnbr_fd(-987441, 1);
	printf("\n");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n");
}*/