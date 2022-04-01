/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:58:50 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/20 22:17:30 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	get_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i += 1;
	return (i);
}

int	env_cmp(char *arg, char *env, t_addlist *list)
{
	int		i;
	int		diff;
	char	**words_env;
	char	**words_arg;

	words_arg = ft_split(arg, '=');
	if (!words_arg)
		freer(list, 1);
	words_env = ft_split(env, '=');
	if (!words_env)
		freer(list, 1);
	diff = up_strncmp(words_arg[0], words_env[0]);
	i = -1;
	while (words_arg[++i])
		free (words_arg[i]);
	i = -1;
	while (words_env[++i])
		free (words_env[i]);
	free(words_arg);
	free(words_env);
	return (diff);
}
