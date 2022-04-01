/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:03:11 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 18:03:11 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	while (str && ((9 <= str[i] && str[i] <= 13) || str[i] == ' '))
		i++;
	sign = 1;
	if (str && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (str && str[i] && '0' <= str[i] && str[i] <= '9')
		res = res * 10 + sign * (str[i++] - '0');
	return (res);
}
