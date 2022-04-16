/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:02:07 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/16 13:58:11 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	writecdpath(t_head *head, t_list *args, int stat_lock)
{
	char	*path;

	if (head->fds.envfds)
		readenv(&head->env, head->path, ft_strjoin(":", head->path),
			((int *)ft_lstlast(head->fds.envfds)->content)[0]);
	if (ft_strncmp(args->content, "cd", -1) || stat_lock)
		return ;
	if (ft_lstsize(args) > 1)
		path = args->next->content;
	else
		path = findenv("HOME", ft_strlen("HOME"), head, FALSE);
	ft_putendl_fd(path, head->fds.path[1]);
	cd(head->prog, path, &head->env);
	if (ft_lstsize(args) == 1)
		free(path);
}

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
