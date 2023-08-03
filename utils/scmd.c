/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:08:43 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/04 02:27:52 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_cmd(char **cmd, char *content)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	if (cmd)
		while (cmd[i])
			i++;
	new = malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		new[j] = cmd[j];
		j++;
	}
	new[j++] = ft_strdup(content);
	new[j] = NULL;
	if (cmd)
		free(cmd);
	return (new);
}

t_scmd	*last_scmd(t_scmd *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_rdir	rdir_type(char *content)
{
	if (content[0] == INDIR)
	{
		if (ft_strlen(content) == 1)
			return (infile);
		else
		{
			return (heredoc);
		}
	}
	else
	{
		if (ft_strlen(content) == 1)
			return (outfile);
		else
			return (append);
	}
}

void	get_file(t_file *file, char *rdir, char *filename)
{
	file->type = rdir_type(rdir);
	file->filename = filename;
}

int	count_rdir(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != is_pipe)
	{
		if (token->type == is_rdir)
			i++;
		token = token->next;
	}
	return (i);
}


