/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:00:11 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 14:51:33 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	stop(char *shell_name)
{
	if (errno != 0 && errno != 1)
	{
		ft_putstr_fd(shell_name, 2);
		perror(": export");
		exit(1);
	}
	if (errno == 0)
		exit(0);
	else
		exit(1);
}

void	final_print(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (i > 1)
			printf("%s\n", av[i]);
	}
}

void	distributor(char **av, char **env)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (env[++i])
	{
		j = 1;
		flag = 0;
		while (av[++j])
		{
			flag = 0;
			if (!env_cmp(env[i], av[j], av[0]))
			{
				if (ft_strchr(av[j], '='))
				{
					printf("%s\n", av[j]);
					flag = 1;
				}
				av_remove(av, j);
			}
			else
				continue ;
		}
		if (!flag)
			printf("%s\n", env[i]);
	}
}

int	main(int ac, char **av, char **env)
{
	errno = 0;
	if (ac < 3)
		no_args(env);
	else
	{
		validator(av);
		distributor(av, env);
	}
	final_print(av);
	return (0);
}
