/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:11:38 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:11:40 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	ss1 = (const unsigned char *) s1;
	ss2 = (const unsigned char *) s2;
	i = 0;
	while (ss1 && ss2 && i < n)
	{
		if (ss1[i] - ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i < n)
		return (ss1[i] - ss2[i]);
	return (0);
}
