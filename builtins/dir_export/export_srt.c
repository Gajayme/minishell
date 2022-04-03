/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_srt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:11:46 by lyubov            #+#    #+#             */
/*   Updated: 2022/04/03 16:47:28 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	get_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i += 1;
	return (i);
}

void	env_srt(char **env)
{
	int	i;
	int	j;
	int	len;

	len = get_len(env);
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - 1 - i)
		{
			if (up_strncmp(env[j], env[j + 1]) > 0)
				env_swap(&env[j], &env[j + 1]);
		}
	}
}

void	env_swap(char **arr_1, char **arr_2)
{
	char	*tmp;

	tmp = *arr_1;
	*arr_1 = *arr_2;
	*arr_2 = tmp;
}

void	no_args(char **env)
{
	int		i;
	int		j;
	int		counter;

	i = -1;
	env_srt(env);
	while (env[++i])
	{
		j = -1;
		counter = 0;
		while (env[i][++j])
		{
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && !counter)
			{
				write(1, "\"", 1);
				counter += 1;
			}
		}
		if (counter)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
}
