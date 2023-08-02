/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:08:43 by ksaelim           #+#    #+#             */
/*   Updated: 2023/08/02 23:25:42 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_2d(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char **get_cmd(char **cmd, char *content)
{
	char **new;
	int i;
	int j;

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
t_scmd *last_scmd(t_scmd *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_rdir rdir_type(char *content)
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

void get_file(t_file *file, char *rdir, char *filename)
{
	file->type = rdir_type(rdir);
	file->filename = filename;
}

int count_rdir(t_token *token)
{
	int i;

	i = 0;
	while (token && token->type != is_pipe)
	{
		if (token->type == is_rdir)
			i++;
		token = token->next;
	}
	return (i);
}

t_scmd *create_scmd(t_token **token)
{
	t_scmd *new;
	int n_rdir;
	int i;

	new = (t_scmd *)malloc(sizeof(t_scmd));
	if (!new)
		return (NULL);
	i = 0;
	new->cmd = NULL;
	n_rdir = count_rdir(*token);
	if (n_rdir)
		new->file = malloc(sizeof(t_file) * (n_rdir + 1));
	else
		new->file = NULL;
	while (*token && (*token)->type != is_pipe)
	{
		if ((*token)->type == is_arg)
			new->cmd = get_cmd(new->cmd, (*token)->content);
		else if ((*token)->type == is_rdir)
		{
			get_file(&new->file[i++], (*token)->content, (*token)->next->content);
			*token = (*token)->next;
		}
		*token = (*token)->next;
	}
	if (new->file)
		new->file[i].type = none;
	if (*token && (*token)->type == is_pipe)
		*token = (*token)->next;
	new->next = NULL;
	return (new);
}

void ft_add_scmd(t_scmd **lst, t_scmd *new)
{
	t_scmd *back;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			back = last_scmd(*lst);
			back->next = new;
		}
	}
}

void clear_scmd(t_scmd **lst)
{
	t_scmd *tmp;

	if (!lst || !(*lst))
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->cmd)
			ft_double_free((*lst)->cmd);
		if ((*lst)->file)
			free((*lst)->file);
		if (*lst)
			free(*lst);
		*lst = tmp;
	}
}