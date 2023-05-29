/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktunchar <ktunchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:12:18 by ktunchar          #+#    #+#             */
/*   Updated: 2023/04/27 20:03:32 by ktunchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
/*
int	main()
{
	t_list a,b,c;
	t_list *t;

	a.content = "a";
	b.content = "b";
	c.content = "c";
	
	a.next = &b;
	b.next = &c;
	c.next = NULL;
	
	ft_lstclear()



}*/
