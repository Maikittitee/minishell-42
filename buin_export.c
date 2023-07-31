/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buin_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:16:54 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/01 02:38:37 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static	int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}


static void	sort_export(char **tmp)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	size = strstrlen(tmp);
	while (i < size && tmp[i + 1])
	{
		if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
		{
			s = NULL;
			s = tmp[i];
			tmp[i] = tmp[i + 1];
			tmp[i + 1] = s;
		}
		i++;
	}
}


static int	prt_env_alpha(void)
{
	char **tmp;
	int	i;
	
	tmp = dup_env(global_data.env_ptr);
	sort_export(tmp);
	i = 0;
	while (tmp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	ft_double_free(tmp);
	return (EXIT_SUCCESS);
	
}

static int	export_to_env(char *s)
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
	if (!arg[1])
	{
		// return (1);
		printf("bp1\n");
		return (prt_env_alpha());
	}
	i = 1;
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
