/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:02:23 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/03 21:17:22 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmdnotfound(char *prog, char *place)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(place, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	redirerr(char *prog, char *place)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(place, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	exit(1);
}

void	parserr(char *prog, char *place)
{
	ft_putstr_fd(prog, 2);
	if (!istoken(place, STPSYMBS))
		ft_putstr_fd(": parse error near '", 2);
	else
		ft_putstr_fd(": unexpected token '", 2);
	if (*place == '\0')
		ft_putstr_fd("\\n", 2);
	else
		ft_putchar_fd(*place, 2);
	ft_putendl_fd("'", 2);
	exit(1);
}

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
	ft_putendl_fd(strerror(errno), 2);
	exit(1);
}
