/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialsigns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:54:16 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 21:43:04 by dcelsa           ###   ########.fr       */
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

static void	specialfiller(char *crsr, t_head *head, t_list **exps, t_list *qtxt)
{
	t_bounds	line;

	line.begin = crsr;
	line.end = crsr + ft_strlen(crsr);
	if (!istoken(line.begin, "~$"))
		line.begin = symbdefiner(&line, "~$", qtxt);
	if (*line.begin == '$' && *(line.begin + 1))
		line.begin = dlrhndlr(line.begin, head, exps, qtxt);
	else if (*line.begin == '~'
		&& (istoken(line.begin + 1, " /&?") || !*(line.begin + 1))
		&& (line.begin == crsr || istoken(line.begin - 1, " &|")))
	{
		ft_lstadd_back(exps, ft_lstnew(malloc(sizeof(t_exp))));
		expcast(ft_lstlast(*exps))->sns.begin = line.begin;
		expcast(ft_lstlast(*exps))->sns.end = ++line.begin;
		(expcast(ft_lstlast(*exps))->val) = slash(line.begin,
				findenv("HOME", ft_strlen("HOME"), head, FALSE));
	}
	else
		return ;
	specialfiller(line.begin, head, exps, qtxt);
}

static int	linesize(char *cmd, t_list *crsr)
{
	int		size;

	size = ft_strlen(cmd);
	while (crsr)
	{
		size += expcast(crsr)->sns.begin - expcast(crsr)->sns.end
			+ ft_strlen(expcast(crsr)->val);
		crsr = crsr->next;
	}
	size = size * (size > 0) + (size <= 0);
	return (size);
}

static char	*newcmdbuilder(char *cmd, t_list *exps)
{
	char	*new;
	char	*crs;
	int		size;

	size = linesize(cmd, exps);
	new = ft_bzero(malloc(sizeof(*new) * size), size);
	crs = new;
	while (exps)
	{
		if (cmd != expcast(exps)->sns.begin)
			ft_strlcpy(crs, cmd, expcast(exps)->sns.begin - cmd + 1);
		crs += ft_strlen(crs);
		cmd = expcast(exps)->sns.end;
		ft_strlcat(crs, expcast(exps)->val, ft_strlen(expcast(exps)->val) + 1);
		crs += ft_strlen(crs);
		exps = exps->next;
	}
	crs += ft_strlen(crs);
	if (*cmd)
		ft_strlcat(crs, cmd, ft_strlen(cmd) + 1);
	return (new);
}

char	*expandspecialsigns(char *oldcmd, t_head *head, t_list **qtxt)
{
	t_list	*expansions;
	char	*cmd[2];

	*qtxt = NULL;
	quotedtxt(oldcmd, head->prog, qtxt, FALSE);
	expansions = NULL;
	specialfiller(oldcmd, head, &expansions, *qtxt);
	cmd[0] = oldcmd;
	if (expansions)
		cmd[0] = newcmdbuilder(oldcmd, expansions);
	ft_lstclear(&expansions, &clearexp);
	ft_lstclear(qtxt, &free);
	*qtxt = NULL;
	quotedtxt(cmd[0], head->prog, qtxt, FALSE);
	wildcardhndlr(cmd[0], head, &expansions, *qtxt);
	if (expansions)
	{
		cmd[1] = newcmdbuilder(cmd[0], expansions);
		if (cmd[0] != oldcmd)
			free(cmd[0]);
		cmd[0] = cmd[1];
	}
	ft_lstclear(&expansions, &clearexp);
	return (cmd[0]);
}
