/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_acess.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:35:55 by gajayme           #+#    #+#             */
/*   Updated: 2022/03/20 22:39:51 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	path_freer(char **d_path, char *cmd)
{
	int	i;

	i = -1;
	while (d_path[++i])
		free(d_path[i]);
	if (cmd)
		free(cmd);
	return (1);
}

//F_OK OR X_OK
char	*path_parse(char **env, char *cmd)
{
	int		i;
	char	*u_path;
	char	**d_path;
	char	*full_cmd;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (env[i] && ft_strncmp(env[i], "PATH", 4))
		i ++;
	u_path = ft_strtrim(env[i], "PATH=");
	d_path = ft_split(u_path, ':');
	free(u_path);
	i = 0;
	while (d_path[i])
	{
		full_cmd = ft_strjoin(d_path[i++], cmd);
		if (access(full_cmd, F_OK) == 0 && path_freer(d_path, cmd))
			return (full_cmd);
		free(full_cmd);
		full_cmd = NULL;
	}
	path_freer(d_path, cmd);
	return (NULL);
}

char	*cmd_checker(char **env, char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	else
		return (path_parse(env, cmd));
}
