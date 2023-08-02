/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:29:00 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/02 12:26:45 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_echo(char **arg)
{
	int	i;
	int	n;
	int	no_nl;

	i = 1;
	no_nl = 0;
	n = strstrlen(arg);
	if (arg[i] && ft_strnstr(arg[i], "-n", 2))
	{
		i++;
		no_nl = 1;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (i != n - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!no_nl)
		ft_putchar_fd('\n', STDOUT_FILENO);

	return (EXIT_SUCCESS);
}
