/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:59:40 by dcelsa            #+#    #+#             */
/*   Updated: 2022/03/04 18:00:24 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "libft.h"

int	filler(unsigned char c, unsigned long i, int num, int base)
{
	int	j;

	j = 1;
	if (c)
		while (i--)
			ft_putchar_fd(c, 1);
	else
	{
		while ((num / base || i / (unsigned long)base) && ++j)
		{
			num /= base;
			i /= (unsigned long)base;
		}
	}
	return (j);
}

char	*dlc_runner(char *cpy, int *d, int *prs, int *padding)
{
	size_t	i;

	while (*cpy && !d[4])
	{
		d[4] = 1;
		if ((*cpy == ' ' || *cpy == '+') && ++cpy && !--d[4] && d[0] != '+')
			d[0] = *(cpy - 1);
		if ((*cpy == '-' || *cpy == '0') && ++cpy && (!d[4] || !--d[4]))
			d[1] = *(cpy - 1) * (d[1] != '-') + d[1] * (d[1] == '-');
		if (*cpy == '#' && ++cpy && (!d[4] || !--d[4]))
			d[2] = '#';
		if (*cpy != '0' && ft_isdigit(*cpy) && (d[4] || !d[4]++))
			*padding = ft_atoi(cpy);
		cpy += filler(0, *padding, 0, 10) * (*padding > 0);
	}
	while ((*cpy == '.' || *cpy == '0') && ++cpy)
		d[3] = '.';
	*prs = ft_atoi(cpy);
	cpy += filler(0, *prs, 0, 10) * (*prs > 0) + (!*prs && ft_isdigit(*cpy));
	i = -1;
	while (FLAGS[++i])
		if (*cpy == FLAGS[i])
			d[4] = *cpy;
	return (cpy);
}

int	shifter(int *d, int cnt)
{
	int		shift;
	int		i;
	char	f;

	i = 0;
	if (d[4] == 's' || d[4] == 'c' || d[4] == '%' || d[4] == 1)
		shift = cnt * (!d[3] || d[5] > cnt) + d[5] * (d[3] && cnt >= d[5]);
	else
		shift = d[5] * (d[5] >= cnt) + cnt * (cnt > d[5]);
	shift = d[6] - shift;
	shift *= shift > 0;
	f = ' ';
	i = -1;
	while (d[1] == '0' && d[4] != 1 && FLAGS[++i] && FLAGS[i] != d[4])
		;
	if (d[1] == '0' && ((i < 3 || d[4] == 1) || !d[3]))
		f = '0';
	filler(f, shift, 0, 0);
	return (shift);
}

void	putnbr_base(char d, unsigned long un, int n)
{
	int	base;
	int	s;

	s = 1 * (n >= 0) - 1 * (n < 0);
	d = d * (d != 'p') + 'x' * (d == 'p');
	base = 10 * (!(d == 'x' || d == 'X')) + 16 * (d == 'x' || d == 'X');
	if (un / base || n / base)
		putnbr_base(d, un / base, n / base);
	if ((un + n) % base > 9)
		ft_putchar_fd(((un % base) - 10 + 'A' - ('X' - d)), 1);
	else
		ft_putchar_fd(((int)(un % base) + s * (n % base)) + '0', 1);
}
