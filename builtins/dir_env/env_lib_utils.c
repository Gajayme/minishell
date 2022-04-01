/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:11:46 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/20 22:33:37 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	up_strncmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i += 1;
	}
	return (s1[i] - s2[i]);
}

t_addlist	*up_lstnew(char *line, int flag, t_addlist *list)
{
	t_addlist	*node;

	node = (t_addlist *)malloc(sizeof(t_addlist));
	if (!node)
		freer(list, 1);
	node->line = line;
	node->add_flag = 0;
	if (flag)
		node->add_flag = 1;
	return (node);
}

void	up_lstadd_front(t_addlist **lst, t_addlist *new)
{
	if (!new)
		return ;
	new -> next = (*lst);
	(*lst) = new;
}

int	up_lstsize(t_addlist *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		if (lst->add_flag)
			i += 1;
		lst = lst -> next;
	}
	return (i);
}
