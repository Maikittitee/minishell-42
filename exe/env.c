/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:06:40 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 21:37:00 by ktunchar         ###   ########.fr       */
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

char	**dup_env(char **env)
{
	char	**new_env;
	int		nline;
	int		i;

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

t_dict	**get_env_dict(char **env)
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
		if (tmp[0])
			dict[i]->key = ft_strdup(tmp[0]);
		else
			dict[i]->key = NULL;
		if (tmp[1])
			dict[i]->value = ft_strdup(tmp[1]);
		else
			dict[i]->value = ft_strdup("");
		ft_double_free(tmp);
		i++;
	}
	dict[i] = NULL;
	return (dict);
}

char	*get_value2(t_dict **dict, char *target_str)
{
	int	i;

	if (!dict)
		return (NULL);
	if (!target_str)
		return (NULL);
	i = 0;
	while (dict[i])
	{
		if (!ft_strncmp(dict[i]->key, target_str, ft_strlen(target_str) + 1))
			return (dict[i]->value);
		i++;
	}
	return (NULL);
}

int	add_new_env(char *new_env)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (strstrlen(g_global_data.env_ptr) + 2));
	while (g_global_data.env_ptr[i])
	{
		new_envp[i] = ft_strdup(g_global_data.env_ptr[i]);
		i++;
	}
	if (ft_strchr(new_env, '='))
		new_envp[i] = ft_strdup(new_env);
	else
		new_envp[i] = ft_strjoin(new_env, "=");
	new_envp[i + 1] = NULL;
	ft_double_free(g_global_data.env_ptr);
	g_global_data.env_ptr = new_envp;
	update_env_dict();
	return (1);
}
