/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajayme <gajayme@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:58:50 by gajayme           #+#    #+#             */
/*   Updated: 2022/04/03 16:59:17 by gajayme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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

int	word_freer(char **words)
{
	int	i;

	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
	return (0);
}

int	env_cmp(char *arg, char *env, char *shell_name)
{
	int		diff;
	char	**words_env;
	char	**words_arg;

	words_arg = ft_split(arg, '=');
	if (!words_arg)
		stop(shell_name);
	words_env = ft_split(env, '=');
	if (!words_env && !word_freer(words_arg))
		stop(shell_name);
	diff = up_strncmp(words_arg[0], words_env[0]);
	word_freer(words_arg);
	word_freer(words_env);
	return (diff);
}

int	err_print(char *arg, char *shell_name)
{
	ft_putstr_fd(shell_name, 2);
	ft_putstr_fd(": export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

int	up_putendl_fd(char *s, int fd)
{
	if (!s)
		return (0);
	while (*s)
	{
		write(fd, s, 1);
		s += 1;
	}
	write(fd, "\n", 1);
	return (0);
}
