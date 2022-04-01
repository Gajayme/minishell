/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:44:39 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/31 17:34:23 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && (i < n - 1))
	{
		i += 1;
	}
	return (s1[i] - s2[i]);
}

void	flag(char **av)
{
	int	i;
	int	j;

	i = 2;
	j = i + 1;
	while (av[++i] && av[++j])
		printf("%s ", av[i]);
	if (av[i])
		printf("%s", av[i]);
}

void	no_flag(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = i + 1;
	while (av[++i] && av[++j])
		printf("%s ", av[i]);
	if (av[i])
		printf("%s", av[i]);
	printf("\n");
}

int	main(int ac, char **av)
{
	if (ac < 3)
		printf("\n");
	else if (ft_strncmp(av[2], "-n", 3) == 0)
		flag(av);
	else
		no_flag(av);
	return (0);
}
