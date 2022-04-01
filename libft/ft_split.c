/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:12:36 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 19:12:46 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*shifter(char const *s, char c)
{
	size_t	i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	return (&str[i]);
}

static void	puk(size_t *w, size_t *l, size_t *ll, char **ss)
{
	if (++(*w) && ll)
		ll[*w - 1] = *l;
	if (ss)
		ss[*w - 1][*l] = '\0';
	*l = 0;
}

static size_t	counter(char const *s, char c, size_t *ll, char **ss)
{
	size_t	i;
	size_t	w;
	size_t	l;
	char	*str;

	w = 0;
	l = 0;
	i = 0;
	str = shifter(s, c);
	while (str[i])
	{
		if (i && str[i - 1] != c && str[i] == c)
			puk(&w, &l, ll, ss);
		if (str[i++] != c)
			if (++l && ss)
				ss[w][l - 1] = str[i - 1];
	}
	if (i && str[i - 1] != c)
		puk(&w, &l, ll, ss);
	return (w);
}

static void	*erase(char **ss, size_t i)
{
	while (i)
		free(ss[--i]);
	free(ss);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ss;
	size_t	*ll;
	size_t	w;
	size_t	i;

	if (!s)
		return (NULL);
	w = counter(s, c, NULL, NULL);
	ll = malloc(sizeof(*ll) * w);
	ss = malloc(sizeof(*ss) * counter(s, c, ll, NULL) + 1);
	i = 0;
	while (ss && ll && i < w)
	{
		ss[i] = malloc(sizeof(*ss[i]) * (ll[i] + 1));
		if (!(ss[i++]))
			return (erase(ss, i - 1));
	}
	counter(s, c, NULL, ss);
	if (ss)
		ss[w] = NULL;
	free(ll);
	return (ss);
}
