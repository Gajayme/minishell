/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 21:27:51 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/16 21:36:51 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*line_builder(char *str, char *buf, char **shift, int sw)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i++] == '\n')
		{
			*shift = buf + i;
			break ;
		}
	}
	if (sw)
		return (NULL);
	return (remal(str, buf, i));
}

static char	*trunc(char *str, char *buf, char **shift)
{
	char	*sshift;

	if (!buf)
	{
		*shift = NULL;
		return (NULL);
	}
	sshift = NULL;
	line_builder(NULL, buf, &sshift, 1);
	if (sshift && !*sshift)
		sshift = NULL;
	*shift = sshift;
	if (!sshift)
		return (NULL);
	buf = sshift;
	*(buf - 1) += 1;
	str = line_builder(str, buf, &sshift, 0);
	*shift = sshift;
	if (sshift == buf)
		*shift = NULL;
	return (str);
}

char	*get_next_line(int fd)
{
	ssize_t			ret;
	char			*shift;
	static char		*buf = NULL;
	char			*str;

	str = NULL;
	str = trunc(str, buf, &shift);
	if ((size_t) BUFFER_SIZE < 1)
		return (NULL);
	if (!buf)
		buf = malloc(sizeof(*buf) * ((size_t) BUFFER_SIZE + 1));
	ret = BUFFER_SIZE;
	while (buf && !shift)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((!ret || ret == -1) && !erase(NULL, (void **)&buf))
			break ;
		buf[ret] = '\0';
		str = line_builder(str, buf, &shift, 0);
		if (!str)
			return (erase(str, (void **)&buf));
	}
	return (str);
}
