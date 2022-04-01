#include "minishell.h"

void	removeusedbracket(t_list **brackets)
{
	t_list	*outbracket;
	t_list	*prevoutbracket;
	t_list	*inbracket;

	outbracket = getprevstruct(*brackets, ft_lstlast(*brackets));
	inbracket = lstcast(outbracket);
	outbracket->content = inbracket->next;
	free(inbracket);
	prevoutbracket = getprevstruct(*brackets, outbracket);
	if (!prevoutbracket || outbracket->content)
		return ;
	prevoutbracket->next = outbracket->next;
	free(outbracket);
}

char	**cmdarr(t_list *args, t_bool itargs)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(*arr) * ft_lstsize(args) + 1);
	i = 0;
	while (args)
	{
		if (itargs)
			arr[i++] = argcast(args)->arg;
		else
			arr[i++] = args->content;
		args = args->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_list	*getprevstruct(t_list *begin, t_list *crnt)
{
	if (begin == crnt)
		return (NULL);
	while (begin->next != crnt)
		begin = begin->next;
	return (begin);
}

int	structindex(t_list *begin, t_list *curcmd)
{
	int	i;

	i = 0;
	while (begin != curcmd && (++i || !i))
		begin = begin->next;
	return (i);
}
