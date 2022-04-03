/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:34:13 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 19:18:09 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

unsigned long	unsigned_atoi(const char *str)
{
	unsigned long	res;
	int				negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res);
}

long	up_atoi(const char *str)
{
	long	res;
	int		negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

int	up_putstr_fd(char *s, int fd)
{
	if (!s)
		return (0);
	while (*s)
	{
		write(fd, s, 1);
		s += 1;
	}
	return (0);
}

int	get_len(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i += 1;
	return (i);
}
