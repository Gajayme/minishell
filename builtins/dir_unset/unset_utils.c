/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:58:52 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/31 19:05:14 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

int	up_strncmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i += 1;
	}
	return (s1[i] - s2[i]);
}

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
	int		i;

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

void	err_finder(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (bad_chars(av[i]) && !err_print(av[i], av[0]))
		{
			av_remove(av, i);
			i -= 1;
			errno = 1;
		}
	}
}

int	env_cmp(char *arg, char *env, char *shell_name)
{
	int		i;
	int		diff;
	char	**words_env;

	words_env = ft_split(env, '=');
	if (!words_env)
		stop(shell_name);
	diff = up_strncmp(arg, words_env[0]);
	i = -1;
	while (words_env[++i])
		free (words_env[i]);
	free(words_env);
	return (diff);
}
