/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:59:47 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 20:48:14 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirdefiner(t_bounds *cmd, t_list **redirs, t_list *qtxt)
{
	t_bounds	rdr;

	rdr.begin = cmd->begin;
	if (!istoken(rdr.begin, "<>"))
		rdr.begin = symbdefiner(cmd, "<>", qtxt);
	if (rdr.begin == cmd->end)
		return ;
	ft_lstadd_back(redirs, ft_lstnew(malloc(sizeof(t_redir))));
	rdrcast(ft_lstlast(*redirs))->src = (*rdr.begin == '<');
	rdrcast(ft_lstlast(*redirs))->apporstdin = (*rdr.begin == *(rdr.begin + 1));
	rdr.begin += 1 + rdrcast(ft_lstlast(*redirs))->apporstdin;
	while (*rdr.begin && *rdr.begin == ' ')
		rdr.begin++;
	rdr.end = cmd->end;
	rdr.end = symbdefiner(&rdr, "<> |&", qtxt);
	rdr.end -= istoken(rdr.end, "<> |&");
	(rdrcast(ft_lstlast(*redirs))->florlmt) = txtcopy(&rdr, NULL, qtxt, TRUE);
	rdr.begin = rdr.end + 1;
	rdr.end = cmd->end;
	if (rdr.begin >= rdr.end)
		return ;
	redirdefiner(&rdr, redirs, qtxt);
}

static void	cmdbuilder(t_bounds *cmd, t_cmd *curcmd, t_list *qtxt)
{
	t_bounds	word;
	t_bool		wastoken;

	curcmd->args = NULL;
	redirdefiner(cmd, &curcmd->redirs, qtxt);
	cmd->begin += istoken(cmd->begin, "|&");
	while (cmd->begin < cmd->end)
	{
		while (cmd->begin < cmd->end && *cmd->begin == ' ')
			cmd->begin++;
		wastoken = istoken(cmd->begin, STPSYMBS);
		if (wastoken)
			cmd->begin += 1 + (*(cmd->begin + 1) == *cmd->begin);
		while (cmd->begin < cmd->end && *cmd->begin == ' ')
			cmd->begin++;
		word.begin = cmd->begin;
		word.end = symbdefiner(cmd, "<> |&", qtxt);
		word.end -= istoken(word.end, "<> |&") + (!*word.end);
		cmd->begin = word.end + 1;
		if (wastoken || (word.end - word.begin < 1 && *word.end == ' '))
			continue ;
		txtcopy(&word, &curcmd->args, qtxt, FALSE);
	}
}

static void	priordefiner(t_cmd *curcmd, t_bounds *cmd, char *cmds)
{
	curcmd->ispipe = (*cmd->end == '|' && *(cmd->end + 1) != '|');
	curcmd->lprior = '\0';
	if (cmd->begin == cmds)
		return ;
	curcmd->ispipe += (*cmd->begin == '|' && *(cmd->begin - 1) != '|');
	if ((*cmd->begin == '|' && *(cmd->begin - 1) == '|') || *cmd->begin == '&')
		curcmd->lprior = *cmd->begin;
}

void	parser(t_head *head, t_list **cmdlst)
{
	t_bounds	cmd;
	t_cmd		*curcmd;
	t_list		*qtxt;

	qtxt = NULL;
	quotedtxt(head->cmd, head->prog, &qtxt, FALSE);
	cmd.begin = head->cmd;
	while (cmd.begin < head->cmd + ft_strlen(head->cmd))
	{
		cmd.end = cmd.begin + ft_strlen(cmd.begin);
		cmd.end = symbdefiner(&cmd, SYMBS, qtxt);
		curcmd = malloc(sizeof(*curcmd));
		curcmd->ispipe = FALSE;
		priordefiner(curcmd, &cmd, head->cmd);
		curcmd->redirs = NULL;
		cmdbuilder(&cmd, curcmd, qtxt);
		ft_lstadd_back(cmdlst, ft_lstnew(curcmd));
		cmd.begin = cmd.end + (*cmd.end == *(cmd.end + 1));
	}
	ft_lstclear(&qtxt, &free);
}
