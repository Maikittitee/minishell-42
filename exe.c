/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:22:15 by ktunchar          #+#    #+#             */
/*   Updated: 2023/06/11 21:28:45 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	main(int ac, char **av, char **env)
{
	char *input;

	while (ft_strncmp(input, "exit", 5))
	{
		input = readline("minishell$ ");
		printf("%s\n", input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		free(input);
	}
	free(input);

	// if (!is_pipe())
	// 	// do_exe();
	// else
	// 	// pipex();

}