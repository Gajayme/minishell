/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:57:04 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 19:28:08 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pathdefiner(char *prog, char **env)
{
	char	**path;
	char	*bpath;
	int		acs;
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", ft_strlen("PATH=")))
			break ;
	if (!ft_strnstr(env[i], "PATH=", -1))
		return (NULL);
	path = ft_split(env[i] + ft_strlen("PATH="), ':');
	i = arrsize(path);
	while (--i >= 0)
	{
		bpath = ft_strjoin(path[i], prog);
		acs = access_checker(bpath);
		if (!acs && eraser(path))
			return (bpath);
		free(bpath);
		if (acs == -2 && eraser(path))
			return (NULL);
	}
	eraser(path);
	return (NULL);
}

static int	executor(t_cmd *cmd, char **env, char *prog, t_bool isbuiltin)
{
	char	**flags;
	char	*buf;
	char	*path;

	flags = cmdarr(cmd->args);
	if (!flags)
		return (error_handler(prog, cmd->args->content, -1));
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(flags[0 + isbuiltin], '/'))
	{
		path = flags[isbuiltin];
		flags[isbuiltin] = ft_strrchr(flags[isbuiltin], '/') + 1;
		return (error_handler(prog, path, execve(path, flags, env)));
	}
	buf = ft_strjoin("/", flags[isbuiltin]);
	path = pathdefiner(buf, env);
	free(buf);
	if (!path || !*flags[isbuiltin])
		return (cmdnotfound(prog, flags[isbuiltin]));
	return (error_handler(prog, flags[isbuiltin], execve(path, flags, env)));
}

static t_bool	closefdsandskipprnths(t_fds *fds, int leftpfd[2], t_head *head)
{
	t_prnths	*prnth;

	if (leftpfd && leftpfd[0])
		close(leftpfd[0]);
	if (leftpfd && leftpfd[1])
		close(leftpfd[1]);
	if (fds->envfds)
		close(((int *)ft_lstlast(fds->envfds)->content)[1]);
	prnth = inprnths(boundcast(cmdcast(head->pipe)->words)->begin, head->prnths);
	if (!prnth)
		return (TRUE);
	while (prnth->edges.begin < boundcast(cmdcast(head->crsr)->words)->begin
		&& boundcast(cmdcast(head->crsr)->words)->begin < prnth->edges.end)
		head->crsr = head->crsr->next;
	return (TRUE);
}

static void	prnthshndlr(t_cmd *curcmd, t_head *head, int leftpfd[2], int rightpfd[2])
{
	t_prnths	*prnth;

	prnth = inprnths(boundcast(curcmd->words)->begin, head->prnths);
	if (!prnth)
		return ;
	// ft_lstclear(&head->pipe, NULL);
	while (head->crsr
		&& prnth->edges.begin < boundcast(cmdcast(head->crsr)->words)->begin
		&& boundcast(cmdcast(head->crsr)->words)->begin < prnth->edges.end)
	{
		ft_lstadd_back(&head->pipe, ft_lstnew(head->crsr->content));
		head->crsr = head->crsr->next;
	}
	rdrhndlr(NULL, prnth, NULL, head);
	mounter(leftpfd, rightpfd, prnth->fd, head->prog);
	// printf("zasdasd\n");
	head->prnths = leavebranch(prnth, head->prnths);
	ft_lstclear(&head->fds.envfds, &free);
	head->crsr = head->pipe;
	while (head->crsr)
		head->referr = pipehndlr(head);
	exit(head->referr);
}

int	forker(t_list *curcmd, t_head *head, int rightpfd[2], pid_t *pidsfd)
{
	int			leftpfd[2];
	int			strindx;
	t_bool		isbuiltin;

	ft_bzero(leftpfd, sizeof(*leftpfd) * 2);
	if (getprevstruct(head->pipe, curcmd)
		&& !error_handler(head->prog, NULL, pipe(leftpfd)))
		forker(getprevstruct(head->pipe, curcmd), head, leftpfd, pidsfd);
	arghndlr(cmdcast(curcmd)->words, cmdcast(curcmd)->args, cmdcast(curcmd), head);
	pipeenv(cmdcast(curcmd), head->prnths, &head->fds.envfds);
	strindx = structindex(head->pipe, curcmd);
	pidsfd[strindx] = error_handler(head->prog, NULL, fork());
	if (pidsfd[strindx] && closefdsandskipprnths(&head->fds, leftpfd, head))
		return (0);
	free(pidsfd);
	if (head->fds.envfds)
		close(((int *)ft_lstlast(head->fds.envfds)->content)[0]);
	prnthshndlr(cmdcast(curcmd), head, leftpfd, rightpfd);
	rdrhndlr(cmdcast(curcmd), NULL, &head->fds, head);
	builtinhndlr(cmdcast(curcmd), head, &isbuiltin);
	mounter(leftpfd, rightpfd, cmdcast(curcmd)->fd, head->prog);
	return (executor(cmdcast(curcmd), cmdarr(head->env), head->prog,
			isbuiltin));
}
