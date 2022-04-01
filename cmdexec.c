#include "minishell.h"

static int	grand_finale(int pidcount, pid_t *pids, char *prog)
{
	int	i;
	int	stat_lock;

	i = -1;
	while (++i < pidcount)
		error_handler(prog, NULL, waitpid(pids[i], NULL, WUNTRACED));
	free(pids);
	return (WEXITSTATUS(stat_lock));
}

t_bool	skippedcmd(int referr, t_list **crsr)
{
	char	ref;

	ref = '&' * (!!referr) + '|' * (!referr);
	if (!(*crsr) || cmdcast(*crsr)->lprior != ref)
		return (FALSE);
	while (*crsr &&
		(cmdcast(*crsr)->lprior == ref || cmdcast(*crsr)->ispipe))
		*crsr = (*crsr)->next;
	return (TRUE);
}

int	pipehndlr(t_head *head, t_list **crsr)
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
	head->referr = grand_finale(pipecmds, pids, head->prog);
	ft_lstclear(&head->pipe, NULL);
	return (head->referr);
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
	crsr = cmdlst;
	while (crsr)
		head->referr = pipehndlr(head, &crsr);
	ft_lstclear(&cmdlst, &clearcmdlst);
	exit(head->referr);
}
