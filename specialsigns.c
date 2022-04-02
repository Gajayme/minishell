/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialsigns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:54:16 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 15:54:20 by dcelsa           ###   ########.fr       */
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

t_bool	rediravoider(char *crsr, char *cmd, t_bool forwld)
{
	if (!forwld && crsr > cmd && istoken(crsr, "~$") && crsr--)
		while (crsr > cmd && *crsr == ' ')
			crsr--;
	if (forwld && crsr > cmd)
		while (crsr > cmd && !istoken(crsr, "<>&|"))
			crsr--;
	if (istoken(crsr, "<>"))
		return (TRUE);
	return (FALSE);
}

static void	specialfiller(char *crsr, t_head *head, t_list **exps, t_list *qtxt)
{
	t_bounds	line;

	line.begin = crsr;
	line.end = crsr + ft_strlen(crsr);
	if (!istoken(line.begin, "~$"))
		line.begin = symbdefiner(&line, "~$", qtxt);
	if (!head->isredir && rediravoider(line.begin, head->cmd, FALSE))
		line.begin++;
	else if (*line.begin == '$')
		line.begin = dlrhndlr(line.begin, head, exps, qtxt);
	else if (*line.begin == '~'
		&& (istoken(line.begin + 1, " /") || !*(line.begin + 1))
		&& (line.begin == head->cmd || *(line.begin - 1) == ' '))
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

static char	*newcmdbuilder(char *cmd, t_list *crsr, t_list *exps)
{
	char	*new;
	char	*crs;
	int		size;

	size = ft_strlen(cmd);
	while (crsr)
	{
		size += expcast(crsr)->sns.begin - expcast(crsr)->sns.end
			+ ft_strlen(expcast(crsr)->val);
		crsr = crsr->next;
	}
	new = malloc(sizeof(*new) * size);
	crs = new;
	while (exps)
	{
		crs += ft_strlen(crs);
		if (cmd != expcast(exps)->sns.begin)
			ft_strlcpy(crs, cmd, expcast(exps)->sns.begin - cmd + 1);
		crs += ft_strlen(crs);
		cmd = expcast(exps)->sns.end;
		ft_strlcat(crs, expcast(exps)->val, ft_strlen(expcast(exps)->val) + 1);
		exps = exps->next;
	}
	return (new);
}

void	expandspecialsigns(t_head *head, t_list **qtxt)
{
	t_list	*expansions;
	char	*cmd;

	*qtxt = NULL;
	quotedtxt(head->cmd, head->prog, qtxt, FALSE);
	expansions = NULL;
	specialfiller(head->cmd, head, &expansions, *qtxt);
	if (expansions)
	{
		cmd = newcmdbuilder(head->cmd, expansions, expansions);
		free(head->cmd);
		head->cmd = cmd;
	}
	ft_lstclear(&expansions, &clearexp);
	*qtxt = NULL;
	quotedtxt(head->cmd, head->prog, qtxt, FALSE);
	wildcardhndlr(head->cmd, head, &expansions, *qtxt);
	if (expansions)
	{
		cmd = newcmdbuilder(head->cmd, expansions, expansions);
		free(head->cmd);
		head->cmd = cmd;
	}
	ft_lstclear(&expansions, &clearexp);
}
