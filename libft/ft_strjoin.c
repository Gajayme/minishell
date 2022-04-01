/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:51:28 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/04 22:05:57 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	str = malloc(i + j + 1);
	i = 0;
	while (str && s1 && s1[i++])
		str[i - 1] = s1[i - 1];
	j = 0;
	while (str && s2 && s2[j++])
		str[i + j - 2] = s2[j - 1];
	if (str && (i || j))
		str[i + j - 1 - (i && j)] = '\0';
	if (str && !i && !j)
		str[0] = '\0';
	return (str);
}
