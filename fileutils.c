/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:57:09 by dcelsa            #+#    #+#             */
/*   Updated: 2022/03/28 19:18:58 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handler(char *prog, char *place, int funcres)
{
	if (funcres >= 0)
		return (funcres);
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	if (place)
		ft_putstr_fd(place, 2);
	if (place)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

int	eraser(char **p)
{
	char	**c;

	c = p;
	while (*p)
		free(*p++);
	free(*p);
	free(c);
	return (1);
}

int	arrsize(char **argv)
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}
