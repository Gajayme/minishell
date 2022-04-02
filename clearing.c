/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:52:52 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 15:52:53 by dcelsa           ###   ########.fr       */
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

static void	clearargs(void *content)
{
	free(((t_arg *)content)->arg);
}

void	clearcmdlst(void *content)
{
	ft_lstclear(&((t_cmd *)content)->args, &clearargs);
}
