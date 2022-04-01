/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:56:47 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 18:56:48 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pow10(size_t i)
{
	int	res;

	res = 1;
	while (i--)
		res *= 10;
	return (res);
}

static char	*rec(int n, size_t i, char *str, int *f)
{
	if ((i < 10 && n < 0 && n / pow10(i))
		|| (i < 9 && n >= 0 && (n / pow10(i + 1))))
		str = rec(n, i + 1, str, f);
	while ((n < 0 && i != 10 && n / pow10(i))
		|| (n >= 0 && i != 9 && n / pow10(i + 1)))
		n = n / 10;
	if (!str && *f)
	{
		str = malloc(sizeof(*str) * i + 2);
		if (!str)
			*f = 0;
		else
			str[i + 1] = '\0';
	}
	if (*f)
		str[i] = -1 * (n < 0) * (n % 10) + (n >= 0) * (n % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		f;

	str = NULL;
	f = 1;
	if (n >= 0)
		str = rec(n, 0, str, &f);
	else
	{
		str = rec(n, 1, str, &f);
		if (str)
			str[0] = '-';
	}
	return (str);
}
