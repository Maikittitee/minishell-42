/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:58:43 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 21:06:17 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

void	main_handler(int signum)
{
	(void)signum;
	g_global_data.return_code = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	exec_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	exit(130);
}

bool	set_signal(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigemptyset(&sigint.sa_mask);
	sigemptyset(&sigquit.sa_mask);
	sigint.sa_handler = &main_handler;
	sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
	return (true);
}
