/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:00:20 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 16:00:23 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*txtcopy(t_bounds *bounds, t_list **args, t_list *qtxt, t_bool skipqts)
{
	char	*crsr;
	char	*begin;
	int		size;
	int		i;

	size = bounds->end - bounds->begin + 2;
	crsr = bounds->begin;
	while (!skipqts && crsr <= bounds->end)
		if (*(crsr++) == '"' || *(crsr - 1) == '\'')
			size--;
	crsr = malloc(sizeof(*crsr) * size);
	begin = bounds->begin;
	i = 0;
	while (begin <= bounds->end)
		if (!(istoken(begin, "\"'") && outqt(begin, qtxt, FALSE) && begin++)
			|| skipqts)
			crsr[i++] = *(begin++);
	crsr[i] = '\0';
	if (!args)
		return (crsr);
	ft_lstadd_back(args, ft_lstnew(malloc(sizeof(t_arg))));
	argcast(ft_lstlast(*args))->arg = crsr;
	argcast(ft_lstlast(*args))->word = bounds->begin;
	return (crsr);
}

char	*symbdefiner(t_bounds *cmd, char *symbs, t_list *qtxt)
{
	char	*symb;
	char	*buf;

	symb = cmd->end;
	while (*symbs)
	{
		buf = ft_strchr(cmd->begin + 1, *(symbs++));
		if (!(cmd->begin < buf && buf < symb))
			continue ;
		if (outqt(buf, qtxt, FALSE))
		{
			symb = buf;
			continue ;
		}
		while (buf && !outqt(buf, qtxt, FALSE) && buf < symb)
			buf = ft_strchr(buf + 1, *(symbs - 1));
		if (cmd->begin < buf && buf < symb && outqt(buf, qtxt, FALSE))
			symb = buf;
	}
	return (symb);
}

t_bool	istoken(char *str, char *tokens)
{
	while (*tokens)
		if (*str == *(tokens++))
			return (TRUE);
	return (FALSE);
}

int	arrsize(char **argv)
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

int	eraser(char **p)
{
	char	**c;

	c = p;
	while (*p)
		free(*p++);
	free(*p);
	free(c);
	return (1);
}
