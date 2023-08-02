/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_pwd_env_cd_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 23:40:45 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/02 22:32:57 by ksaelim          ###   ########.fr       */
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
	while (global_data.env_ptr[i])
	{
		printf("%s\n", global_data.env_ptr[i]);
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
		gogo = get_value2(global_data.env_dict, "HOME");
	if (chdir(gogo) == -1)
		return (raise_error(NULL, 0));
	newpwd = NULL;
	newpwd = getcwd(newpwd, 0);
	printf("the new pwd is %s\n", newpwd);
	if (change_env("PWD", newpwd))
		printf("Success\n");
	else
		printf("CHANGE FAIL\n");
	if (get_value2(global_data.env_dict, "OLDPWD"))
		change_env("OLDPWD", oldpwd);
	free(newpwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}

int	ft_exit(char **arg)
{
	int	code;
	int	i;

	code = 0;
	i = 1;
	while (arg[i])
	{
		if (i > 1)
			return (printf("exit: too many arguments\n"), EXIT_FAILURE);
		if (!ft_atol(arg[1]))
		{
			printf("exit\n");
			printf("exit: %s ", arg[i]);
			printf(": numeric argument required\n");
			// free();
			// free();
			exit(255);
		}
		i++;
	}
	printf("exit\n");
	// ft_free();
	return (exit(code), 0);
}
