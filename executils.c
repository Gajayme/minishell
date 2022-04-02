/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:02:07 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 19:43:56 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmdarr(t_list *args, t_bool itargs)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(*arr) * ft_lstsize(args) + 1);
	i = 0;
	while (args)
	{
		if (itargs)
			arr[i++] = argcast(args)->arg;
		else
			arr[i++] = args->content;
		args = args->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_list	*getprevstruct(t_list *begin, t_list *crnt)
{
	if (begin == crnt)
		return (NULL);
	while (begin->next != crnt)
		begin = begin->next;
	return (begin);
}

int	structindex(t_list *begin, t_list *curcmd)
{
	int	i;

	i = 0;
	while (begin != curcmd && (++i || !i))
		begin = begin->next;
	return (i);
}

static t_bool	addprogname(char *cmd, char *prog, t_list **args,
	t_bool *isbuiltin)
{
	*isbuiltin = FALSE;
	if (!ft_strncmp(cmd, "echo", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(malloc(sizeof(t_arg))));
	if (!ft_strncmp(cmd, "pwd", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(malloc(sizeof(t_arg))));
	if (!ft_strncmp(cmd, "export", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(malloc(sizeof(t_arg))));
	if (!ft_strncmp(cmd, "unset", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(malloc(sizeof(t_arg))));
	if (!ft_strncmp(cmd, "env", -1) && ++(*isbuiltin))
		ft_lstadd_front(args, ft_lstnew(malloc(sizeof(t_arg))));
	if (!*isbuiltin)
		return (TRUE);
	argcast(*args)->arg = ft_strdup(prog);
	return (TRUE);
}

void	builtinhndlr(t_cmd *cmd, t_list *env, t_head *head, t_bool *isbuiltin)
{
	if (!ft_strncmp(argcast(cmd->args)->arg, "exit", -1))
		ft_exit(head->prog, cmdarr(cmd->args, TRUE));
	if (!ft_strncmp(argcast(cmd->args)->arg, "cd", -1))
	{
		if (ft_lstsize(cmd->args) > 1)
			exit(cd(head->prog, argcast(cmd->args->next)->arg, &head->env));
		exit(cd(head->prog, NULL, &head->env));
	}
	if (!cmd->ispipe && addprogname(argcast(cmd->args)->arg, head->prog,
			&cmd->args, isbuiltin))
		return ;
	if ((!ft_strncmp(argcast(cmd->args)->arg, "export", -1)
			&& ft_lstsize(cmd->args) > 2)
		|| !ft_strncmp(argcast(cmd->args)->arg, "unset", -1))
		close(cmd->fd[1]);
	addprogname(argcast(cmd->args)->arg, head->prog, &cmd->args, isbuiltin);
}
