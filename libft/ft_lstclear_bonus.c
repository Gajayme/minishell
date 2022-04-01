/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:57:18 by dcelsa            #+#    #+#             */
/*   Updated: 2022/03/20 22:21:19 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*begin;
	t_list	*tmp;

	begin = (*lst);
	while (begin)
	{
		if (del)
			del(begin->content);
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
	*lst = NULL;
}
