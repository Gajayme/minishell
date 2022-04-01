/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:57:41 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 18:57:42 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	*erase(t_list *begin, void (*del)(void *))
{
	t_list	*tmp;

	while (begin)
	{
		if (del)
			del(begin->content);
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*begin;
	t_list	*prev;

	prev = NULL;
	begin = NULL;
	while (lst)
	{
		new = malloc(sizeof(*new));
		if (!begin)
			begin = new;
		if (!new)
			return (erase(begin, del));
		if (f)
			new->content = f(lst->content);
		lst = lst->next;
		if (prev)
			prev->next = new;
		prev = new;
	}
	if (prev)
		prev->next = NULL;
	return (begin);
}
