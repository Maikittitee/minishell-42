/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 04:27:31 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:27:55 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	break_input(char *line, t_token **token)
{
	int		len;
	int		qoute;
	int		dollar;
	char	*str;

	while (*line)
	{
		qoute = 0;
		dollar = 0;
		while (*line && *line == ' ')
			line++;
		len = valid_quote(line, &qoute, &dollar);
		if (!len)
			return (FALSE);
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return (FALSE);
		ft_strlcpy(str, line, len + 1);
		classify_add_token(token, create_token(str, qoute, dollar, len));
		line += len;
	}
	return (TRUE);
}
