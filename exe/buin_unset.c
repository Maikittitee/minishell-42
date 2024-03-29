/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:25:27 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 00:24:22 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

void	print_unset_err(char *s)
{
	if (!s)
		return ;
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_unset(char **arg)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	if (!arg)
		return (0);
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!is_valid_var(arg[i]))
		{
			print_unset_err(arg[i]);
			err = 1;
		}
		else
			delete_env(arg[i]);
		i++;
	}
	return (err);
}
