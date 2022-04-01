/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 00:45:14 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/31 18:35:36 by lyubov           ###   ########.fr       */
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

int	bad_chars(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if ((arg[i] > 31 && arg[i] < 47) || (arg[i] > 57 && arg[i] < 65)
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
	char	**words;

	i = 1;
	while (av[++i])
	{
		words = ft_split(av[i], '=');
		if (!words)
		{
			stop(av[0]);
		}
		if ((bad_chars(words[0]) || av[i][0] == '=')
				&& !err_print(av[i], av[0]))
		{
			errno = 1;
			av_remove(av, i);
			i -= 1;
		}
		j = -1;
		while (words[++j])
			free (words[j]);
		free (words);
	}
}
