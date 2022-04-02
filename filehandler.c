/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filehandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:57:13 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/02 16:01:25 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_check(char *file, int mod, t_bool app, char *prog)
{
	int	fd;

	fd = 0;
	if (!access(file, F_OK) && !access(file, mod))
		fd = open(file, O_RDWR);
	if ((mod == R_OK && !fd) || (fd == -1 && errno == 21))
		error_handler(prog, file, -1);
	if (mod == R_OK && ((fd > 0 && !close(fd)) || fd))
		fd = error_handler(prog, file, open(file, O_RDONLY));
	if (mod == W_OK && !app && ((fd > 0 && !close(fd)) || fd))
		fd = error_handler(prog, file, open(file,
					O_WRONLY | O_TRUNC | O_APPEND));
	else if (mod == W_OK && ((fd > 0 && !close(fd)) || fd))
		fd = error_handler(prog, file, open(file, O_WRONLY | O_APPEND));
	else if (!fd)
		fd = error_handler(prog, file, open(file,
					O_WRONLY | O_CREAT | O_EXCL | O_APPEND, 420));
	if (!fd || fd == -1)
		error_handler(prog, file, -1);
	return (fd);
}

int	access_checker(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (0);
		return (-2);
	}
	return (-1);
}

int	maninp(char *limiter)
{
	int		pfd[2];
	char	*buf;

	while (pipe(pfd))
		;
	while (1)
	{
		ft_putstr_fd("> ", 1);
		buf = get_next_line(0);
		if (!buf)
			continue ;
		if (ft_strnstr(buf, limiter, -1)
			&& ft_strlen(buf) - 1 == ft_strlen(limiter))
		{
			close(pfd[1]);
			return (pfd[0]);
		}
		ft_putstr_fd(buf, pfd[1]);
	}
	return (-1);
}

void	mounter(int leftpfd[2], int rightpfd[2], int fd[2], char *prog)
{
	if (rightpfd[0])
		error_handler(prog, NULL, close(rightpfd[0]));
	if (fd[0])
	{
		error_handler(prog, NULL, dup2(fd[0], 0));
		error_handler(prog, NULL, close(fd[0]));
	}
	else if (leftpfd[0])
		error_handler(prog, NULL, dup2(leftpfd[0], 0));
	if (leftpfd[0])
		error_handler(prog, NULL, close(leftpfd[0]));
	if (fd[1] != 1)
	{
		error_handler(prog, NULL, dup2(fd[1], 1));
		error_handler(prog, NULL, close(fd[1]));
	}
	else if (rightpfd[1])
		error_handler(prog, NULL, dup2(rightpfd[1], 1));
	if (leftpfd[1])
		error_handler(prog, NULL, close(leftpfd[1]));
	if (rightpfd[1])
		error_handler(prog, NULL, close(rightpfd[1]));
}
