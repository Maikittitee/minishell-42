/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:16:54 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/01 01:51:16 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	ft_isvar(int c)
{
	if (c == '_' || ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_varlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '_' || ft_isalpha(s[i]))
		i++;
	else
		return (0);
	while (s[i] && ft_isvar(s[i]))
		i++;
	return (i);
	
}

int	is_valid_var(char *s)
{
	int	varlen;
	
	if (!s)
		return (0);
	if (s[0] == '_' || ft_isalpha(s[0]))
	{
		varlen = ft_varlen(s);
		if (s[varlen] == '\0' || s[varlen] == '=')
			return (1);
	}
	return (0);
		
}

int	export_to_env(char *s)
{
	char **split;
	char *key;
	char *value;

	key = NULL;
	value = NULL;
	split = ft_split(s, '=');
	if (split[0])
		key = split[0];
	if (split[1])
		value = split[1];
	printf("bp1 %s %s\n", key, value);
	if (get_value(global_data.env_dict, key))
	{
		printf("bp2\n");
		change_env(key, value);
	}
	else
		add_new_env(s);
	ft_double_free(split);
	return (1);
}

int	ft_export(char **arg)
{
	int	i;
	int	err;

	err = 0;
	if (!arg)
		return (0);
	if (!*arg)
		return (1);
		// return (display_env_alpha());
	i = 0;
	while (arg[i])
	{
		if (!is_valid_var(arg[i]))
		{
			// print_export_err(arg[i]);
			err = 1;
		}
		else
			export_to_env(arg[i]);
		i++;
	}
	return (err);
}
