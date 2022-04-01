/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 23:41:14 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/31 16:30:16 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	freer(t_addlist *list, int flag)
{
	t_addlist	*tmp;

	while (list)
	{
		free (list->line);
		tmp = list;
		list = list->next;
		free (tmp);
	}
	if (flag)
	{
		if (errno != 0 && errno != 1)
			perror("env");
		exit (1);
	}
}

void	err_print(char *arg, int flag, t_addlist *list)
{
	errno = 1;
	if (!flag)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		freer (list, 1);
	}
	ft_putstr_fd("env: setenv ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Invalid argument\n", 2);
	freer(list, 1);
}

char	*wrapper(char *funk, t_addlist *list)
{
	if (!funk)
		freer(list, 1);
	return (funk);
}
