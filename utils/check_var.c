/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 04:17:45 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:22:52 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_1stchar_var(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

int	ft_isvar(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

int	ft_varlen(char *token)
{
	int	i;

	i = 0;
	if (check_1stchar_var(token[i]))
		i++;
	while (ft_isvar(token[i]))
		i++;
	return (i);
}
