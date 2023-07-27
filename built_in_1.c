/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:40:45 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/28 02:48:06 by ktunchar         ###   ########.fr       */
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
	exit (EXIT_SUCCESS);
}

int	ft_cd(char **arg)
{
	char *oldpwd;
	char *newpwd;
	char *gogo;
	oldpwd = NULL;
	
	oldpwd = getcwd(oldpwd, 0);
	if (arg[1])
		gogo = arg[1];
	else
		gogo = dict_get_by_key(global_data.env_dict, "HOME");
	printf("to do is %s\n", gogo);
	if (chdir(gogo) == -1)
		return (raise_error(NULL, 0));
	newpwd = NULL;
	newpwd = getcwd(newpwd, 0);
	printf("the new pwd is %s\n", newpwd);
	if (change_env(global_data.env_ptr, "PWD", newpwd))
		printf("Success\n");
	else
		printf("CHANGE FAIL\n");
	if (dict_get_by_key(global_data.env_dict, "OLDPWD"))
		change_env(global_data.env_ptr, "OLDPWD", oldpwd);
		
	free(newpwd);
	free(oldpwd);

	// update_dict
	return (EXIT_SUCCESS);
	
	
		
		
		
		

}
