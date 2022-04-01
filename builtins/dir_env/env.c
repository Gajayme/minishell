/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:00:11 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/31 16:31:23 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	no_args(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
	}
}

void	distributor(char **av, char **env, t_addlist **list)
{
	char	*cmd;

	av++;
	while (*(++av))
	{
		cmd = cmd_checker(env, *av);
		if (cmd)
			execve(cmd, av, add_to_env(*list, env));
		else if (ft_strchr(*av, '=') && *av[0] != '=')
			change_or_new(*av, env, list);
		else if (*av[0] == '=')
			err_print(*av, 1, *list);
		else
			err_print(*av, 0, *list);
	}
	no_args(add_to_env(*list, env));
	freer(*list, 0);
}

int	main(int ac, char **av, char **env)
{
	t_addlist	*list;

	errno = 0;
	list = NULL;
	if (ac < 3)
		no_args(env);
	else
		distributor(av, env, &list);
	return (0);
}
