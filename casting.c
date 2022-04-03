/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:53:01 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/03 15:35:54 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bounds	*boundcast(t_list *lst)
{
	return (lst->content);
}

t_cmd	*cmdcast(t_list *lst)
{
	return (lst->content);
}

t_redir	*rdrcast(t_list *lst)
{
	return (lst->content);
}

t_exp	*expcast(t_list *lst)
{
	return (lst->content);
}
