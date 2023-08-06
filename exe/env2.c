/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:48:05 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 21:53:06 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	change_env(char *key, char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	if (value == NULL)
		return (0);
	while (g_global_data.env_ptr[i])
	{
		if (ft_strncmp(g_global_data.env_ptr[i], key, ft_strlen(key)) == 0)
		{
			tmp = ft_strjoin(key, "=");
			free(g_global_data.env_ptr[i]);
			g_global_data.env_ptr[i] = ft_strjoin(tmp, value);
			update_env_dict();
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	delete_env(char *key)
{
	char	**new_envp;
	int		i;
	int		j;

	if (!get_value2(g_global_data.env_dict, key))
		return (0);
	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (strstrlen(g_global_data.env_ptr)));
	while (g_global_data.env_ptr[i])
	{
		if (ft_strncmp(g_global_data.env_ptr[i], key, ft_strlen(key)) != 0)
		{
			new_envp[j] = ft_strdup(g_global_data.env_ptr[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	ft_double_free(g_global_data.env_ptr);
	g_global_data.env_ptr = new_envp;
	update_env_dict();
	return (1);
}

void	update_env_dict(void)
{
	ft_free_dict(g_global_data.env_dict);
	g_global_data.env_dict = get_env_dict(g_global_data.env_ptr);
}

int	is_exist(t_dict **dict, char *target_str)
{
	int	i;

	if (!dict)
		return (0);
	if (!target_str)
		return (0);
	i = 0;
	while (dict[i])
	{
		if (!ft_strncmp(dict[i]->key, target_str, ft_strlen(target_str) + 1))
			return (1);
		i++;
	}
	return (0);
}

int	replace_env(char *key, char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	while (g_global_data.env_ptr[i])
	{
		if (ft_strncmp(g_global_data.env_ptr[i], key, ft_strlen(key)) == 0)
		{
			tmp = ft_strjoin(key, "=");
			free(g_global_data.env_ptr[i]);
			g_global_data.env_ptr[i] = ft_strjoin(tmp, value);
			update_env_dict();
			free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}
