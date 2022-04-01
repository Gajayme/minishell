/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:12:04 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:12:05 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	cc;
	char			*str;

	cc = (unsigned char) c;
	str = b;
	i = 0;
	while (i < len)
		str[i++] = cc;
	return (b);
}
