/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:02:07 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/03 16:49:50 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmdarr(t_list *args)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(*arr) * (ft_lstsize(args) + 1));
	i = 0;
	while (args)
	{
		arr[i++] = args->content;
		args = args->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_list	*getprevstruct(t_list *begin, t_list *crnt)
{
	if (begin == crnt)
		return (NULL);
	while (begin->next != crnt)
		begin = begin->next;
	return (begin);
}

int	structindex(t_list *begin, t_list *curcmd)
{
	int	i;

	i = 0;
	while (begin != curcmd && (++i || !i))
		begin = begin->next;
	return (i);
}
