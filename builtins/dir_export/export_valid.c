/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:45:14 by lyubov            #+#    #+#             */
/*   Updated: 2022/04/03 19:07:30 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	av_remove(char **av, int num)
{
	int	i;

	i = num;
	while (av[i])
	{
		num += 1;
		av[i] = av[num];
		i += 1;
	}
}

void	remove_duplicate(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[++i])
	{
		j = i;
		while (av[++j])
		{
			if (!env_cmp(av[i], av[j], av[1]))
				av_remove(av, i);
		}
	}
}

int	bad_chars(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] && arg[i] != '=')
	{
		if ((arg[i] > 31 && arg[i] < 48) || (arg[i] > 57 && arg[i] < 65)
			|| (arg[i] > 90 && arg[i] < 95) || arg[i] == 96
			|| (arg[i] > 122 && arg[i] < 127))
			return (1);
	}
	return (0);
}

void	validator(char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[++i])
	{
		if ((av[i][0] == '=' || ft_isdigit(av[i][0]) || bad_chars(av[i]))
			&& !err_print(av[i], av[1]))
		{
			errno = 1;
			av_remove(av, i);
			i -= 1;
		}
		j = -1;
	}
}
