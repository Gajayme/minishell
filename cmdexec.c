/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:01:52 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/03 01:03:55 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	grand_finale(int pidcount, pid_t *pids, t_head *head, t_list *args)
{
	int	i;
	int	stat_lock;

	i = -1;
	while (++i < pidcount)
		error_handler(head->prog, NULL, waitpid(pids[i], &stat_lock, WUNTRACED));
	free(pids);
	if (pidcount > 1)
		return (stat_lock);
	if (head->fds.envfds)
		readenv(&head->env, head->path, ft_strjoin(":", head->path), ((int *)ft_lstlast(head->fds.envfds)->content)[0]);
	if (ft_strncmp(argcast(args)->arg, "cd", -1) || stat_lock)
		return (stat_lock);
	if (ft_lstsize(args) > 1)
	{
		ft_putstr_fd(argcast(args->next)->arg, head->fds.path[1]);
		cd(head->prog, argcast(args->next)->arg, &head->env);
		return (WEXITSTATUS(stat_lock));
	}
	ft_putstr_fd(findenv("HOME", ft_strlen("HOME"), head, FALSE), head->fds.path[1]);
	cd(head->prog, NULL, &head->env);
	return (stat_lock);
}

t_bool	skippedcmd(int referr, t_list **crsr, t_list *cmdlst)
{
	char	ref;

	ref = '&' * (!!referr) + '|' * (!referr);
	if (!(*crsr) || cmdcast(*crsr)->lprior != ref || *crsr == cmdlst)
		return (FALSE);
	while (*crsr
		&& (cmdcast(*crsr)->lprior == ref || cmdcast(*crsr)->ispipe))
		*crsr = (*crsr)->next;
	return (TRUE);
}

static int	pipehndlr(t_head *head, t_list **crsr, t_list *cmdlst)
{
	pid_t	*pids;
	int		pipecmds;
	int		nullfd[2];

	if (skippedcmd(head->referr, crsr, cmdlst))
		return (head->referr);
	pipecmds = 0;
	head->pipe = NULL;
	while (*crsr && ++pipecmds)
	{
		ft_lstadd_back(&head->pipe, ft_lstnew((*crsr)->content));
		*crsr = (*crsr)->next;
		if (!*crsr || !cmdcast(*crsr)->ispipe)
			break ;
	}
	pids = ft_bzero(malloc(sizeof(*pids) * pipecmds), sizeof(*pids) * pipecmds);
	ft_bzero(nullfd, sizeof(*nullfd) * 2);
	forker(ft_lstlast(head->pipe), head, nullfd, pids);
	head->referr = grand_finale(pipecmds, pids, head, cmdcast(head->pipe)->args);
	ft_lstclear(&head->pipe, NULL);
	return (head->referr);
}

void	rewriteenv(t_list *env, t_fds *fds)
{
	close(fds->path[1]);
	close(fds->ex[1]);
	while (env)
	{
		ft_putstr_fd(env->content, fds->env[1]);
		ft_putstr_fd("\n", fds->env[1]);
		env = env->next;
	}
	close(fds->env[1]);
}

void	handlecmd(t_head *head, int *stat_loc)
{
	pid_t	pid;
	t_list	*cmdlst;
	t_list	*crsr;

	if (!pipe(head->fds.path) && !pipe(head->fds.env))
		pipe(head->fds.ex);
	pid = fork();
	if (pid && !close(head->fds.env[1]) && !close(head->fds.path[1])
		&& !close(head->fds.ex[1]) && waitpid(pid, stat_loc, WUNTRACED))
		return ;
	if (!close(head->fds.env[0]) && !close(head->fds.path[0])
		&& !close(head->fds.ex[0]))
		cmdlst = NULL;
	parser(head, &cmdlst);
	head->fds.envfds = NULL;
	crsr = cmdlst;
	while (crsr)
		head->referr = pipehndlr(head, &crsr, cmdlst);
	rewriteenv(head->env, &head->fds);
	ft_lstclear(&head->fds.envfds, &free);
	ft_lstclear(&cmdlst, &clearcmdlst);
	exit(head->referr);
}
