/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialsigns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:54:16 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 18:11:06 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*slash(char *end, char *home)
{
	if (*end != '/')
		return (home);
	end = ft_strjoin(home, "/");
	free(home);
	return (end);
}

static void	specialfiller(t_bounds crsr, t_head *head, t_list **exps, t_list *qtxt)
{
	if (!istoken(crsr.begin, "~$"))
		crsr.begin = symbdefiner(&crsr, "~$", qtxt);
	if (*crsr.begin == '$')
		crsr.begin = dlrhndlr(crsr, head, exps, qtxt);
	else if (*crsr.begin == '~'
		&& (istoken(crsr.begin + 1, " /") || !*(crsr.begin + 1))
		&& (*(crsr.begin - 1) == ' ' || !*(crsr.begin - 1)))
	{
		ft_lstadd_back(exps, ft_lstnew(malloc(sizeof(t_exp))));
		expcast(ft_lstlast(*exps))->sns.begin = crsr.begin;
		expcast(ft_lstlast(*exps))->sns.end = ++crsr.begin;
		(expcast(ft_lstlast(*exps))->val) = slash(crsr.begin,
				findenv("HOME", ft_strlen("HOME"), head, FALSE));
		while (*crsr.begin == '~')
			crsr.begin++;
	}
	else
		return ;
	specialfiller(crsr, head, exps, qtxt);
}

static t_bounds	*newcmdbuilder(char *begin, char *end, int size, t_list *exps)
{
	t_bounds	*new;

	new = malloc(sizeof(*new));
	new->begin = ft_bzero(malloc(sizeof(*new->begin) * size), sizeof(*new->begin) * size);
	while (exps)
	{
		if (begin != expcast(exps)->sns.begin)
			ft_strlcat(new->begin, begin, expcast(exps)->sns.begin - begin + 1 + ft_strlen(new->begin));
		begin = expcast(exps)->sns.end;
		ft_strlcat(new->begin, expcast(exps)->val, ft_strlen(expcast(exps)->val) + 1 + ft_strlen(new->begin));
		exps = exps->next;
	}
	if (*begin)
		ft_strlcat(new->begin, begin, end - begin + 2 + ft_strlen(new->begin));
	new->end = new->begin + ft_strlen(new->begin);
	return (new);
}

t_bounds	*preparebuilding(t_bounds *src, t_bounds *word, t_list *expansions)
{
	t_bounds	*cmd;
	t_list		*crsr;
	int			size;

	if (!expansions)
		return (src);
	size = src->end - src->begin + 1;
	crsr = expansions;
	while (crsr)
	{
		size += expcast(crsr)->sns.begin - expcast(crsr)->sns.end
			+ ft_strlen(expcast(crsr)->val);
		crsr = crsr->next;
	}
	cmd = newcmdbuilder(src->begin, src->end, size, expansions);
	if (src != word)
	{
		free(src->begin);
		free(src);
	}
	return (cmd);
}

t_bounds	*expandspecialsigns(t_bounds *word, t_head *head, t_list **qtxt)
{
	t_list		*expansions;
	t_bounds	*cmd;

	expansions = NULL;
	specialfiller(*word, head, &expansions, head->qtxt);
	cmd = preparebuilding(word, word, expansions);
	*qtxt = head->qtxt;
	if (expansions)
		*qtxt = NULL;
	if (expansions)
		quotedtxt(cmd->begin, NULL, qtxt);
	ft_lstclear(&expansions, &clearexp);
	wildcardhndlr(*cmd, head, &expansions, *qtxt);
	cmd = preparebuilding(cmd, word, expansions);
	ft_lstclear(&expansions, &clearexp);
	return (cmd);
}
