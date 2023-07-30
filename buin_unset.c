/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:25:27 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/31 01:50:30 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	unset_err(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char **arg)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (!arg)
		return (0);
	if (!*arg)
		return (0);
	while(arg[i])
	{
		if (unset_err(arg[i]))
		{
			raise_error(arg[i], INVALID_IDENTIFIER);
			err = 1;
		}
		else
			delete_env(arg[i]);
		i++;
	}
	return (err)
	
	
}