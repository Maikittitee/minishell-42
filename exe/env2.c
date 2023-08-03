/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:48:05 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 01:48:15 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	change_env(char *key, char *value)
{
	char	*tmp;
	int		i;

	i = 0;
	while (global_data.env_ptr[i])
	{
		if (ft_strncmp(global_data.env_ptr[i], key, ft_strlen(key)) == 0)
		{
			tmp = ft_strjoin(key, "=");
			free(global_data.env_ptr[i]);
			global_data.env_ptr[i] = ft_strjoin(tmp, value);
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

	if (!get_value2(global_data.env_dict, key))
		return (0);
	i = 0;
	j = 0;
	new_envp = malloc(sizeof(char *) * (strstrlen(global_data.env_ptr)));
	while (global_data.env_ptr[i])
	{
		if (ft_strncmp(global_data.env_ptr[i], key, ft_strlen(key)) != 0)
		{
			new_envp[j] = ft_strdup(global_data.env_ptr[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	ft_double_free(global_data.env_ptr);
	global_data.env_ptr = new_envp;
	update_env_dict();
	return (1);
}

void	update_env_dict(void)
{
	ft_free_dict(global_data.env_dict);
	global_data.env_dict = get_env_dict(global_data.env_ptr);
}
