/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:03:40 by lyubov            #+#    #+#             */
/*   Updated: 2022/04/02 18:44:46 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	cd(char *shell_name, char *dirname, t_list **list)
{
	int	flag;

	flag = 0;
	if (!list)
	{
		if (chdir(dirname && pprrr(shell_name, dirname)))
			return (1);
		return (0);
	}
	if (!dirname)
	{
		if (find_home(shell_name, *list, &dirname))
			return (1);
		flag = 1;
	}
	if (dir_changer(dirname, list) && pprrr(shell_name, dirname))
		return (1);
	if (flag)
		free(dirname);
	return (0);
}
