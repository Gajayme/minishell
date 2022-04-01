/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:52:36 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/31 19:05:32 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

void	stop(char *shell_name)
{
	if (errno != 0 && errno != 1)
	{
		ft_putstr_fd(shell_name, 2);
		perror(": unset");
		exit(1);
	}
	if (errno == 0)
		exit(0);
	else
		exit(1);
}

int	err_print(char *arg, char *shell_name)
{
	ft_putstr_fd(shell_name, 2);
	ft_putstr_fd(": unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

void	distributor(char **av, char **env)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	while (env[++i])
	{
		j = 1;
		flag = 0;
		while (av[++j])
		{
			if (env_cmp(av[j], env[i], av[0]))
				continue ;
			flag = 1;
		}
		if (!flag)
			printf("%s\n", env[i]);
	}
	stop(av[0]);
}

int	main(int ac, char **av, char **env)
{
	errno = 0;
	if (ac > 2)
	{
		err_finder(av);
		distributor(av, env);
	}
	return (0);
}
