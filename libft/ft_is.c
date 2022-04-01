/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:04:26 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 18:49:44 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (c);
	return (0);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (c);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (c);
	return (0);
}

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (c + 1);
	return (0);
}

int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (c);
	return (0);
}
