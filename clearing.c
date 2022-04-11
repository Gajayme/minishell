/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:52:52 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/11 19:33:22 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clearexp(void *content)
{
	free(((t_exp *)content)->val);
}

void	clearredirlst(void *content)
{
	free(((t_redir *)content)->florlmt);
}

void	clearcmdlst(void *content)
{
	ft_lstclear(&((t_cmd *)content)->args, &free);
}

void	clearprnths(void *content)
{
	t_prnths	*prnth;

	prnth = prnthscast(content);
	ft_lstclear(&prnth->inprt, &clearprnths);
	ft_lstclear(&prnth->redirs, &clearredirlst);
	free(content);
}

t_list	*leavebranch(t_prnths *prnth, t_list *prnths)
{
	t_list	*head;
	t_list	*tmp;

	head = prnths;
	while (prnths)
	{
		tmp = prnths;
		prnths = prnths->next;
		ft_lstclear(&prnthscast(tmp)->redirs, &clearredirlst);
		if (prnthscast(prnths) == prnth)
			head = prnth->inprt;
		else
			ft_lstclear(&prnthscast(tmp)->inprt, &clearprnths);
		free(tmp);
	}
	return (head);
}
