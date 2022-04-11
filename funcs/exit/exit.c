/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:42:30 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 21:54:43 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	digit_checker(char *arg, char *shell_name, int fd_exit)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (i == 0 && arg[i] == '-')
			continue ;
		else if ((arg[i] < 48 || arg[i] > 57) && !err_printer(arg, shell_name))
			exiting(255, fd_exit);
	}
	return (0);
}

int	overflow_checker(char *arg, char *shell_name, int fd_exit)
{
	unsigned long	max;
	unsigned long	num;

	max = LONG_MAX;
	num = unsigned_atoi(arg);
	if ((ft_strlen(arg) > 20 || ((num > max && *arg != '-')
				|| (num > max + 1 && *arg == '-')))
		&& !err_printer(arg, shell_name))
		exiting(255, fd_exit);
	return (0);
}

void	exiting(int code, int fd_exit)
{
	char	*str;

	str = ft_itoa(code);
	ft_putendl_fd(str, fd_exit);
	free(str);
	exit(code);
}

int	ft_exit(char *shell_name, int fd_exit, char **av)
{
	if (get_len(av) == 1 || (get_len(av) > 1 && av[1][0] == '#'))
		exiting(0, fd_exit);
	else if (get_len(av) <= 2 && !digit_checker(av[1], shell_name, fd_exit)
		&& !overflow_checker(av[1], shell_name, fd_exit))
		exiting(up_atoi(av[1]), fd_exit);
	else if (get_len(av) > 2 && !digit_checker(av[1], shell_name, fd_exit))
	{
		up_putstr_fd("exit\n", 2);
		up_putstr_fd(shell_name, 2);
		up_putstr_fd(": exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
