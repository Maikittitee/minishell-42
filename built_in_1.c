/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:40:45 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/25 16:21:51 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_pwd(char **arg)
{
	char *cwd;
	(void)arg;

	cwd = NULL;
	// if (arg[1])
	// {
	// 	raise_error(arg[0], TOO_MUCH_ARG);
	// 	return (1);
	// }
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
	{
		perror("error: ");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

int	ft_env(char **arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (global_data.env_dict[i])
	{
		printf("%s=%s\n", global_data.env_dict[i]->key, global_data.env_dict[i]->value);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(char **arg)
{
	char *oldpwd;
	char *to_go;

	oldpwd = NULL;
	
	oldpwd = getcwd(oldpwd, 0);
	if (arg[1])
		to_go = ft_strjoin(oldpwd, arg[1]);
	if (chdir(to_go) == -1)
		exit (raise_error(NULL, 0));
	
	
		
		
		
		

}
