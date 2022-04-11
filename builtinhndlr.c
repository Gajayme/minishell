#include "minishell.h"

void	pipeenv(t_cmd *cmd, t_list *prnths, t_list **envfds)
{
	if (!inprnths(boundcast(cmd->words)->begin, prnths)
		&& ft_lstsize(cmd->args) > 1
		&& (!ft_strncmp(cmd->args->content, "export", -1)
		|| !ft_strncmp(cmd->args->content, "unset", -1)))
	{
		ft_lstadd_back(envfds, ft_lstnew(malloc(sizeof(int) * 2)));
		pipe(ft_lstlast(*envfds)->content);
	}
}

static t_bool	addprogname(char *cmd, char *prog, t_list **args,
	t_bool *isbuiltin)
{
	*isbuiltin = FALSE;
	if (!ft_strncmp(cmd, "echo", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(ft_strdup(prog)));
	if (!ft_strncmp(cmd, "pwd", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(ft_strdup(prog)));
	if (!ft_strncmp(cmd, "export", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(ft_strdup(prog)));
	if (!ft_strncmp(cmd, "unset", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(ft_strdup(prog)));
	if (!ft_strncmp(cmd, "env", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(ft_strdup(prog)));
	return (TRUE);
}

void	builtinhndlr(t_cmd *cmd, t_head *head, t_bool *isbuiltin)
{
	if (!ft_strncmp(cmd->args->content, "exit", -1))
		exit(ft_exit(head->prog, head->fds.ex[1], cmdarr(cmd->args)));
	if (!ft_strncmp(cmd->args->content, "cd", -1))
	{
		if (ft_lstsize(cmd->args) > 1)
			exit(cd(head->prog, cmd->args->next->content, &head->env));
		exit(cd(head->prog, NULL, &head->env));
	}
	if (!cmd->ispipe && addprogname(cmd->args->content, head->prog,
									&cmd->args, isbuiltin))
		return ;
	if ((!ft_strncmp(cmd->args->content, "export", -1)
		|| !ft_strncmp(cmd->args->content, "unset", -1)))
	{
		addprogname(cmd->args->content, head->prog, &cmd->args, isbuiltin);
		if (ft_lstsize(cmd->args) < 3)
			close(cmd->fd[1]);
	}
}