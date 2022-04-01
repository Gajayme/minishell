/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:22:14 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/24 12:57:01 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	add_oldpwd(t_list **list, char *old_dir)
{
	char	*newcwd;
	t_list	*node;

	newcwd = up_strjoin("OLDPWD=", old_dir);
	if (!newcwd)
	{
		free(old_dir);
		return (1);
	}
	node = ft_lstnew(newcwd);
	if (!node)
	{
		free (newcwd);
		return (1);
	}
	ft_lstadd_front(list, node);
	return (0);
}

int	change_oldpwd(void **content, char *old_dir)
{
	char	*newcwd;

	newcwd = up_strjoin("OLDPWD=", old_dir);
	if (!newcwd)
	{
		free(old_dir);
		return (1);
	}
	free(*content);
	*content = newcwd;
	return (0);
}

int	env_modify_old(t_list **list, char *old_dir)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && ft_strncmp(tmp->content, "OLDPWD=", 7))
		tmp = tmp->next;
	if (tmp)
	{
		if (change_oldpwd(&(tmp->content), old_dir))
			return (1);
	}
	else
	{
		if (add_oldpwd(list, old_dir))
			return (1);
	}
	return (0);
}
