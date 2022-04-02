/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:01:52 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 20:10:49 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	grand_finale(int pidcount, pid_t *pids, t_head *head, t_list *args)
{
	int	i;
	int	stat_lock;

	i = -1;
	while (++i < pidcount)
		error_handler(head->prog, NULL, waitpid(pids[i], NULL, WUNTRACED));
	free(pids);
	if (pidcount > 1)
		return (WEXITSTATUS(stat_lock));
	if (!ft_strncmp(argcast(args)->arg, "exit", -1) && !stat_lock)
		ft_putstr_fd("1", head->fds.ex[1]);
	if (!ft_strncmp(argcast(args)->arg, "exit", -1) && !stat_lock)
		ft_exit(head->prog, cmdarr(args->next, TRUE));
	if (ft_strncmp(argcast(args)->arg, "cd", -1) || stat_lock)
		return (WEXITSTATUS(stat_lock));
	if (ft_lstsize(args) > 1)
	{
		ft_putstr_fd(argcast(args->next)->arg, head->fds.path[1]);
		cd(head->prog, argcast(args->next)->arg, &head->env);
		return (WEXITSTATUS(stat_lock));
	}
	ft_putstr_fd(findenv("HOME", ft_strlen("HOME"), head, FALSE), head->fds.path[1]);
	cd(head->prog, NULL, &head->env);
	return (WEXITSTATUS(stat_lock));
}

t_bool	skippedcmd(int referr, t_list **crsr)
{
	char	ref;

	ref = '&' * (!!referr) + '|' * (!referr);
	if (!(*crsr) || cmdcast(*crsr)->lprior != ref)
		return (FALSE);
	while (*crsr
		&& (cmdcast(*crsr)->lprior == ref || cmdcast(*crsr)->ispipe))
		*crsr = (*crsr)->next;
	return (TRUE);
}

static int	pipehndlr(t_head *head, t_list **crsr)
{
	pid_t	*pids;
	int		pipecmds;
	int		nullfd[2];

	if (skippedcmd(head->referr, crsr))
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

void	rewriteenv(t_list **envfds, t_fds *fds)
{
	char	*buf;

	close(fds->path[1]);
	close(fds->ex[1]);
	if (!envfds && !close(fds->env[1]))
		return ;
	buf = get_next_line(((int *)ft_lstlast(*envfds)->content)[0]);
	while (buf)
	{
		ft_putstr_fd(buf, fds->env[1]);
		free(buf);
		buf = get_next_line(((int *)ft_lstlast(*envfds)->content)[0]);
	}
	close(fds->env[1]);
	ft_lstclear(envfds, &free);
}

void	handlecmd(t_head *head, int *stat_loc)
{
	pid_t	pid;
	t_list	*cmdlst;
	t_list	*crsr;

	if (!pipe(head->fds.path) && !pipe(head->fds.env) && !pipe(head->fds.ex))
		pid = fork();
	if (pid && !close(head->fds.env[1]) && !close(head->fds.path[1])
		&& !close(head->fds.ex[1]) && waitpid(pid, stat_loc, WUNTRACED))
		return ;
	if (!close(head->fds.env[0]) && !close(head->fds.path[0])
		&& !close(head->fds.ex[0]))
		cmdlst = NULL;
	parser(head, &cmdlst);
	head->referr = 0;
	head->fds.envfds = NULL;
	crsr = cmdlst;
	while (crsr)
		head->referr = pipehndlr(head, &crsr);
	rewriteenv(&head->fds.envfds, &head->fds);
	ft_lstclear(&cmdlst, &clearcmdlst);
	exit(head->referr);
}
