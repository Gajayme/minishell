/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:13:22 by dcelsa            #+#    #+#             */
/*   Updated: 2022/03/25 21:32:24 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	j = 0;
	while (src[j])
		j++;
	i = 0;
	while (dstsize && dst[i] && i < dstsize)
		i++;
	len = i + j;
	j = 0;
	while (dstsize && src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	if (i < dstsize)
		dst[i] = '\0';
	return (len);
}
