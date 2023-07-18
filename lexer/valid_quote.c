/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:50:19 by ksaelim           #+#    #+#             */
/*   Updated: 2023/07/18 14:50:42 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_quote(char *s, int *qoute, int *dollar)
{
	if (ft_isrdir(*s))
		return (skip_rdir(s));
	else
		return (skip_arg(s, qoute, dollar));
}