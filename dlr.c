/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:30:47 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 21:54:57 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	avoidwildcrd(char *word, char *buf, int size)
{
	char	**split;
	char	**cpy;

	split = ft_split(word, '*');
	cpy = split;
	while (*word)
	{
		while (*word == '*')
			if ((++size && buf) || (++word && FALSE))
				*buf++ = *word++;
		size += ft_strlen(*split) + 2 * (!(!*split));
		if (!buf)
			word += ft_strlen(*split);
		if (!buf && *split++)
			continue ;
		*buf++ = '"' * (!ft_strchr(word, '"'))
			+ '\'' * (!(!ft_strchr(word, '"')));
		buf += ft_strlcpy(buf, *split, ft_strlen(*split) + 1);
		*buf++ = '"' * (!ft_strchr(word, '"'))
			+ '\'' * (!(!ft_strchr(word, '"')));
		*buf = '\0';
		word += ft_strlen(*split++);
	}
	return (size + eraser(cpy) - 1);
}

static char	*arrjoiner(char **split)
{
	char	**crsr;
	char	*val;
	char	*buf;
	int		size;

	size = arrsize(split) - 1;
	crsr = split;
	while (*crsr)
		size += avoidwildcrd(*crsr++, NULL, 0);
	val = malloc(sizeof(*val) * size);
	buf = val;
	crsr = split;
	while (*split)
	{
		if (crsr < split)
			*buf++ = ' ';
		buf += avoidwildcrd(*split++, buf, 0);
	}
	return (val + eraser(crsr) - 1);
}

char	*findenv(char *name, int size, t_head *head, t_bool quoted)
{
	t_list	*crsr;

	if (*name == '?')
	{
		if (head->issig)
			return (ft_itoa(128 + WTERMSIG(head->referr)));
		return (ft_itoa(WEXITSTATUS(head->referr)));
	}
	crsr = head->env;
	while (crsr)
	{
		if (quoted && !ft_strncmp(name, crsr->content, size)
			&& *((char *)crsr->content + size) == '=')
			return (ft_strdup(crsr->content + ++size));
		if (!ft_strncmp(name, crsr->content, size)
			&& *((char *)crsr->content + size) == '=')
			return (arrjoiner(ft_split(crsr->content + ++size, ' ')));
		crsr = crsr->next;
	}
	return (ft_strdup(""));
}

char	*dlrhndlr(char *begin, t_head *head, t_list **exps, t_list *qtxt)
{
	t_bounds	word;

	word.begin = begin;
	word.end = word.begin + ft_strlen(word.begin);
	word.end = symbdefiner(&word, "'\" *<>&|$?", qtxt);
	if (word.end == word.begin
		|| (istoken(word.end, " $") && word.end - 1 == word.begin))
		return (word.end);
	ft_lstadd_back(exps, ft_lstnew(malloc(sizeof(t_exp))));
	expcast(ft_lstlast(*exps))->sns.begin = word.begin;
	(expcast(ft_lstlast(*exps))->sns.end) = word.end
		+ !istoken(word.end, "'\" *<>&|$");
	word.begin++;
	word.end -= istoken(word.end, "'\" *<>&|$") + (!*word.end);
	(expcast(ft_lstlast(*exps))->val) = findenv(word.begin,
			word.end - word.begin + 1, head,
			!outqt(word.begin - 1, qtxt, TRUE));
	return (expcast(ft_lstlast(*exps))->sns.end);
}
