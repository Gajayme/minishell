/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:15:13 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:15:14 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;

	i = 0;
	while (s && s[i])
		i++;
	if (i <= start)
		len = 0;
	else if (i - start < len)
		len = i - start;
	substr = malloc(len + 1);
	if (!substr)
		return (substr);
	substr[len] = '\0';
	if (!len)
		return (substr);
	while (len && --len)
		substr[len] = s[start + len];
	if (i > start)
		substr[len] = s[start];
	return (substr);
}
