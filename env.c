/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:06:40 by ktunchar          #+#    #+#             */
/*   Updated: 2023/07/27 21:46:28 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
void	ft_free_dict(t_dict **dict)
{
	int	i;

	i = 0;
	while (dict[i])
	{
		free(dict[i]->key);
		free(dict[i]->value);
		free(dict[i]);
		i++;
	}
	free(dict);
}

char **dup_env(char **env)
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

t_dict **get_env_dict(char **env)
{
	t_dict	**dict;
	char	**tmp;
	int		i;

	i = 0;
	
	dict = malloc(sizeof(t_dict *) * (strstrlen(env) + 1));
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		dict[i] = malloc(sizeof(t_dict));		
		dict[i]->key = ft_strdup(tmp[0]);
		dict[i]->value = ft_strdup(tmp[1]);
		ft_double_free(tmp);
		i++;
	}
	dict[i] = NULL;
	return (dict);
	
	
}

char *dict_get_by_key(t_dict **dict, char *target_str)
{
	int	i;

	if (!dict)
		return (NULL);
	i = 0;
	while (dict[i])
	{
		if (ft_strncmp(dict[i]->key, target_str, ft_strlen(target_str) + 1) == 0)
			return (dict[i]->value);
		i++;
	}
	return (NULL);
	
}


int	add_new_env(char **env, char *new_env)
{
	int	i;
	char **new_envp;

	i = 0;
	new_envp = malloc(sizeof(char *) * (strstrlen(env) + 2));
	while (env[i])
	{
		new_envp[i] = ft_strdup(env[i]);
		i++;
	}
	new_envp[i] = ft_strdup(new_env);
	new_envp[i + 1] = NULL;
	ft_double_free(env);
	env = new_envp;
	return (1);
}

int	change_env(char **env, char *key, char *value)
{
	int	i;
	char *tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
		{
			tmp = ft_strjoin(key, "=");
			free(env[i]);
			env[i] = ft_strjoin(tmp, value);
			printf("env[i] is %s\n", env[i]);
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}


// int	delete_env(char **env, char *key)


// int	update_env_dict(char **env)