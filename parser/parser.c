/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 04:25:49 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 04:56:49 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->token;
	while (tmp)
		ft_add_scmd(&shell->scmd, create_scmd(&tmp));
}
