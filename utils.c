#include "minishell.h"

t_bounds	*boundcast(t_list *lst)
{
	return (lst->content);
}

t_cmd	*cmdcast(t_list *lst)
{
	return (lst->content);
}

t_redir	*rdrcast(t_list *lst)
{
	return (lst->content);
}

t_arg	*argcast(t_list *lst)
{
	return (lst->content);
}

t_list	*lstcast(t_list *lst)
{
	return (lst->content);
}

t_exp	*expcast(t_list *lst)
{
	return (lst->content);
}

void	clearexp(void *content)
{
	free(((t_exp *)content)->val);
}

void	clearredirlst(void *content)
{
	free(((t_redir *)content)->florlmt);
}

static void	clearargs(void *content)
{
	free(((t_arg *)content)->arg);
}

void	clearcmdlst(void *content)
{
	ft_lstclear(&((t_cmd *)content)->args, &clearargs);
}
