/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:12:59 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:12:59 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	cc = (unsigned char)c;
	i = 0;
	while (s[i])
		if (s[i++] == cc)
			return ((char *)&s[--i]);
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
