/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:09:41 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/27 12:55:44 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	add_pwd(t_list **list)
{
	char	buf[PATH_MAX + 1];
	char	*newcwd;
	t_list	*node;

	if (!getcwd(buf, PATH_MAX))
		return (1);
	newcwd = ft_strjoin("PWD=", buf);
	if (!newcwd)
	{
		free(buf);
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

int	change_pwd(void **content)
{
	char	buf[PATH_MAX + 1];
	char	*newcwd;

	if (!getcwd(buf, PATH_MAX))
		return (1);
	newcwd = ft_strjoin("PWD=", buf);
	if (!newcwd)
	{
		free(buf);
		return (1);
	}
	free(*content);
	*content = newcwd;
	return (0);
}

int	env_modify_new(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && ft_strncmp(tmp->content, "PWD=", 4))
		tmp = tmp->next;
	if (tmp)
	{
		if (change_pwd(&tmp->content))
			return (1);
	}
	else
	{
		if (add_pwd(list))
			return (1);
	}
	return (0);
}
