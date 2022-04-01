/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:57:58 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 18:58:18 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		cc;
	const unsigned char	*ss;
	size_t				i;

	cc = (unsigned char) c;
	ss = (const unsigned char *) s;
	i = 0;
	while (ss && i < n)
		if (ss[i++] == cc)
			return ((void *)&s[--i]);
	return (NULL);
}
