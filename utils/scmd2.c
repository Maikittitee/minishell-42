/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scmd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksaelim <ksaelim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 02:24:40 by ktunchar          #+#    #+#             */
/*   Updated: 2023/08/04 03:47:02 by ksaelim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_in_scmd(t_token **token, t_scmd **new)
{
	t_scmd	*tmp;
	int		i;

	tmp = *new;
	i = 0;
	while (*token && (*token)->type != is_pipe)
	{
		if ((*token)->type == is_arg)
			tmp->cmd = get_cmd(tmp->cmd, (*token)->content);
		else if ((*token)->type == is_rdir)
		{
			get_file(&tmp->file[i++], (*token)->content, \
				(*token)->next->content);
			*token = (*token)->next;
		}
		*token = (*token)->next;
	}
	if (tmp->file)
		tmp->file[i].type = none;
}

t_scmd	*create_scmd(t_token **token)
{
	t_scmd	*new;
	int		n_rdir;

	new = (t_scmd *)malloc(sizeof(t_scmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	n_rdir = count_rdir(*token);
	if (n_rdir)
		new->file = malloc(sizeof(t_file) * (n_rdir + 1));
	else
		new->file = NULL;
	put_in_scmd(token, &new);
	if (*token && (*token)->type == is_pipe)
		*token = (*token)->next;
	new->next = NULL;
	return (new);
}

void	ft_add_scmd(t_scmd **lst, t_scmd *new)
{
	t_scmd	*back;

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

void	clear_scmd(t_scmd **lst)
{
	t_scmd	*tmp;

	if (!lst || !(*lst))
		return ;
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

void	free_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
