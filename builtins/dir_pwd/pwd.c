/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 23:17:24 by lyubov            #+#    #+#             */
/*   Updated: 2022/04/02 21:28:46 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void	up_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s += 1;
	}
}

int	main(int ac, char **av)
{
	char	dir[PATH_MAX + 1];

	if (ac != 2)
	{
		up_putstr_fd(av[0], 2);
		up_putstr_fd(": pwd: too many arguments\n", 2);
		return (1);
	}
	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
	return (0);
}
