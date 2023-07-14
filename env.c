/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:06:40 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/14 15:54:15 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char *dup_env(char **env)
{
	int	nline;
	int	i;
	char **new_env;

	i = 0;
	nline = strstrlen(env);
	new_env = malloc(sizeof(char *) * (nline + 1));
	
	while (i < nline)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char *get_env_dict(char **env)
{
	
}

int	update_env_dict(char **env)
{

}