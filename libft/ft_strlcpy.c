/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:13:27 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:13:28 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (dstsize && i < dstsize - 1)
			dst[i] = src[i];
		else if (dstsize && i == dstsize - 1)
			dst[i] = '\0';
		i++;
	}
	if (!src[i] && dstsize && i <= dstsize - 1)
		dst[i] = '\0';
	return (i);
}
