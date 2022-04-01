/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:11:55 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:11:56 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*from;
	unsigned char		*to;
	size_t				i;

	to = (unsigned char *)dst;
	from = (const unsigned char *)src;
	if (!src || !dst)
		return (dst);
	if (src < dst)
		while (len--)
			to[len] = from[len];
	else
	{
		i = 0;
		while (i++ < len)
			to[i - 1] = from[i - 1];
	}
	return (dst);
}
