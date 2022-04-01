/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:15:08 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:15:09 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checker(char const *set, const char c)
{
	size_t	j;

	j = 0;
	while (set[j])
		if (c == set[j++])
			return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	while (s1 && set && s1[start] && !checker(set, s1[start]))
		start++;
	end = start;
	while (s1 && s1[end])
		end++;
	while (end - start && set && !checker(set, s1[end - 1]))
		end--;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
