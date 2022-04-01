/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:26:58 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/16 21:34:59 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

void	*erase(void *p1, void **p2)
{
	if (p1)
		free(p1);
	if (p2 && *p2)
	{
		free(*p2);
		*p2 = NULL;
	}
	return (NULL);
}

static size_t	getlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*remal(char *str, char *buf, size_t len)
{
	size_t	size;
	size_t	addsize;
	size_t	i;
	char	*new_str;

	addsize = BUFFER_SIZE;
	if (BUFFER_SIZE < INIT_BUF_SIZE)
		addsize = INIT_BUF_SIZE;
	size = getlen(str);
	new_str = str;
	if (!size || (size % addsize) + len >= addsize - 1)
		new_str = malloc(sizeof(*new_str) * (size + 1 + addsize));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str && new_str != str && str[++i] && i < size)
		new_str[i] = str[i];
	if (str && new_str != str)
		erase(str, NULL);
	new_str[size + len] = '\0';
	while (len--)
		new_str[size + len] = buf[len];
	return (new_str);
}
