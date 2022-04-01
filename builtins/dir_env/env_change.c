/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyubov <lyubov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:12:06 by lyubov            #+#    #+#             */
/*   Updated: 2022/03/20 22:34:27 by lyubov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_one(char *arg, char **env)
{
	int		env_len;

	env_len = get_len(env);
	env[env_len] = arg;
	env[env_len + 1] = NULL;
}

void	change_one(char *arg, char **env, t_addlist **list)
{
	t_addlist	*node;
	char		*line;

	if (!up_strncmp(arg, *env) || !ft_strchr(arg, '='))
		return ;
	line = wrapper(ft_strdup(arg), *list);
	node = up_lstnew(line, 0, *list);
	up_lstadd_front(list, node);
	*env = line;
}

void	add_to_list(char *arg, t_addlist **list)
{
	char		*line;
	t_addlist	*node;

	line = wrapper(ft_strdup(arg), *list);
	node = up_lstnew(line, 1, *list);
	up_lstadd_front(list, node);
}

char	**add_to_env(t_addlist *list, char **env)
{
	int			i;
	int			new_len;
	char		**new_env;
	t_addlist	*tmp;

	new_len = get_len(env) + up_lstsize(list);
	new_env = (char **)malloc(sizeof(char *) * new_len + 1);
	if (!new_env)
		freer(list, 1);
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i] = NULL;
	tmp = list;
	while (tmp)
	{
		if (tmp->add_flag)
			add_one(tmp->line, new_env);
		tmp = tmp->next;
	}
	return (new_env);
}

void	change_or_new(char *arg, char **env, t_addlist **list)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!env_cmp(arg, env[i], *list))
		{
			change_one(arg, &env[i], list);
			return ;
		}
	}
	add_to_list(arg, list);
}
