/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:49:05 by lyubov            #+#    #+#             */
/*   Updated: 2022/04/03 00:52:13 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	pprrr(char *shell_name, char *dirname)
{
	ft_putstr_fd(shell_name, 2);
	ft_putstr_fd(": cd: ", 2);
	perror(dirname);
	return (1);
}

int	find_curdir(char **cur_dir)
{
	char	buf[PATH_MAX + 1];

	if (!getcwd(buf, PATH_MAX))
		return (1);
	*cur_dir = ft_strdup(buf);
	if (!cur_dir)
		return (1);
	return (0);
}

int	dir_changer(char *dirname, t_list **list)
{
	char	*cur_dir;

	if (find_curdir(&cur_dir))
		return (1);
	if (chdir(dirname))
	{
		free(cur_dir);
		return (1);
	}
	if (env_modify_new(list))
	{
		free(cur_dir);
		return (1);
	}
	if (env_modify_old(list, cur_dir))
	{
		free(cur_dir);
		return (1);
	}
	return (0);
}

int	find_home(char *shell_name, t_list *list, char **home_dir)
{
	while (list && ft_strncmp(list->content, "HOME=", 5))
		list = list->next;
	if (!list)
	{
		ft_putstr_fd(shell_name, 2);
		ft_putendl_fd(": cd: Home not set", 2);
		return (1);
	}
	*home_dir = ft_strdup(list->content + 5);
	if (!home_dir && pprrr(shell_name, NULL))
		return (1);
	return (0);
}
