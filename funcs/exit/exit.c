/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:42:30 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 00:52:35 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	digit_checker(char *arg, char *shell_name)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (i == 0 && arg[i] == '-')
			continue ;
		else if ((arg[i] < 48 || arg[i] > 57) && !err_printer(arg, shell_name))
			exit(255);
	}
	return (0);
}

int	overflow_checker(char *arg, char *shell_name)
{
	unsigned long	max;
	unsigned long	num;

	max = LONG_MAX;
	num = unsigned_atoi(arg);
	if ((ft_strlen(arg) > 20 || ((num > max && *arg != '-')
				|| (num > max + 1 && *arg == '-')))
		&& !err_printer(arg, shell_name))
		exit (255);
	else
		return (0);
}

int	err_printer(char *arg, char *shell_name)
{
	up_putstr_fd("exit\n", 2);
	up_putstr_fd(shell_name, 2);
	up_putstr_fd(": exit ", 2);
	up_putstr_fd(arg, 2);
	up_putstr_fd(": numeric argument required\n", 2);
	return (0);
}

int	ft_exit(char *shell_name, char **av)
{
	if (get_len(av) == 1 || (get_len(av) > 1 && av[1][0] == '#'))
		exit(0);
	else if (get_len(av) <= 2 && !digit_checker(av[1], shell_name)
		&& !overflow_checker(av[1], shell_name))
		exit(up_atoi(av[1]));
	else if (get_len(av) > 2 && !digit_checker(av[1], shell_name))
	{
		up_putstr_fd("exit\n", 2);
		up_putstr_fd(shell_name, 2);
		up_putstr_fd(": exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
