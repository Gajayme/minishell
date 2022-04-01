/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_lib_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:38:51 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/24 00:43:20 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

char	*up_strjoin(char const *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (NULL);
	ft_memmove(ptr, s1, s1_len);
	ft_memmove(ptr + s1_len, s2, s2_len);
	ptr[s1_len + s2_len] = '\0';
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (ptr);
}

int	up_putendl_fd(char *s, int fd)
{
	if (!s)
		return (0);
	while (*s)
	{
		write(fd, s, 1);
		s += 1;
	}
	write(fd, "\n", 1);
	return (0);
}
