/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arghndlr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:44:13 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/16 14:30:51 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	argsexpander(t_list *arg, t_list **args, char **split,
	t_list *qtxt)
{
	t_list		*crsr;
	t_bounds	bounds;
	int			i;

	i = arrsize(split);
	if (!i)
		arg->content = ft_strdup("");
	crsr = arg;
	while (--i >= 0)
	{
		bounds.begin = split[i];
		bounds.end = bounds.begin + ft_strlen(split[i])
			- 1 * (ft_strlen(split[i]) > 0);
		if (arrsize(split) - 1 == i)
			arg->content = txtcopy(&bounds, NULL, qtxt);
		else
			ft_lstadd_front(&crsr, ft_lstnew(txtcopy(&bounds, NULL, qtxt)));
	}
	if (eraser(split) && *args == arg)
		*args = crsr;
	else
		getprevstruct(*args, arg)->next = crsr;
	return (TRUE);
}

static t_bool	needsplit(char *arg, char *prog)
{
	t_bounds	bounds;
	t_list		*qtxt;

	qtxt = NULL;
	quotedtxt(arg, prog, &qtxt, FALSE);
	bounds.begin = arg;
	bounds.end = bounds.begin + ft_strlen(bounds.begin);
	if (*bounds.begin != '$')
		bounds.begin = symbdefiner(&bounds, "$", qtxt);
	if (*bounds.begin != '$' || outqt(bounds.begin, qtxt, TRUE))
	{
		ft_lstclear(&qtxt, &free);
		return (TRUE);
	}
	ft_lstclear(&qtxt, &free);
	return (FALSE);
}

void	arghndlr(t_list *args, t_list **argshead, t_head *head)
{
	t_list		*qtxt;
	t_bounds	new;
	t_bool		spl;

	if (ft_lstsize(args) > 1 && (!ft_strncmp(args->content, "export", -1)
			|| !ft_strncmp(args->content, "unset", -1)))
	{
		ft_lstadd_back(&head->fds.envfds, ft_lstnew(malloc(sizeof(int) * 2)));
		pipe(ft_lstlast(head->fds.envfds)->content);
	}
	while (args)
	{
		new.begin = expandspecialsigns(args->content, head, &qtxt);
		new.end = new.begin + ft_strlen(new.begin) - 1;
		spl = needsplit(args->content, head->prog);
		if (args->content != new.begin)
			free(args->content);
		if (!(spl && argsexpander(args, argshead, ft_split(new.begin, ' '),
					qtxt)))
			args->content = txtcopy(&new, NULL, qtxt);
		else
			free(new.begin);
		ft_lstclear(&qtxt, &free);
		args = args->next;
	}
}

static void	addprogname(char *cmd, char *prog, t_list **args,
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
	addprogname(cmd->args->content, head->prog, &cmd->args, isbuiltin);
	if (!cmd->ispipe || !*isbuiltin)
		return ;
	if ((!ft_strncmp(cmd->args->content, "export", -1)
			&& ft_lstsize(cmd->args) > 2)
		|| !ft_strncmp(cmd->args->content, "unset", -1))
		close(cmd->fd[1]);
}
