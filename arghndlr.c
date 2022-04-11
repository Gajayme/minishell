#include "minishell.h"

static int	expinit(t_list *arg, char *new, char ***split)
{
	t_bounds	bounds;
	int			i;

	*split = ft_split(new, ' ');
	i = arrsize(*split);
	bounds.begin = (*split)[--i];
	bounds.end = bounds.begin + ft_strlen((*split)[i]) - 1;
	arg->content = txtcopy(&bounds, NULL, NULL);
	return (i);
}

static void	argsexpander(t_list *arg, t_list *word, t_cmd *cmd, char *new)
{
	char		**split;
	t_list		*argcrsr;
	t_list		*wordcrsr;
	t_bounds	bounds;
	int			i;

	argcrsr = arg;
	wordcrsr = word;
	i = expinit(arg, new, &split);
	while (--i >= 0)
	{
		bounds.begin = split[i];
		bounds.end = bounds.begin + ft_strlen(split[i]) - 1;
		ft_lstadd_front(&argcrsr, ft_lstnew(txtcopy(&bounds, NULL, NULL)));
		ft_lstadd_front(&wordcrsr, ft_lstnew(wordcrsr->content));
	}
	if (eraser(split) && cmd->args == arg)
	{
		cmd->args = argcrsr;
		cmd->words = wordcrsr;
		return ;
	}
	getprevstruct(cmd->args, arg)->next = argcrsr;
	getprevstruct(cmd->words, word)->next = wordcrsr;
}

static t_bool	needsplit(t_bounds *word, t_list *qtxt)
{
	char	*dlr;

	dlr = word->begin;
	if (*dlr != '$')
		dlr = symbdefiner(word, "$", qtxt);
	if (*dlr == '$' && outqt(dlr, qtxt, TRUE))
		return (TRUE);
	return (FALSE);
}

void	arghndlr(t_list *words, t_list *args, t_cmd *cmd, t_head *head)
{
	t_bounds	*new;
	t_bool		spl;
	t_list		*qtxt;

	while (words)
	{
		qtxt = NULL;
		new = expandspecialsigns(words->content, head, &qtxt);
		spl = needsplit(new, qtxt);
		if (spl)
			argsexpander(args, words, cmd, new->begin);
		else
			ft_lstadd_back(&cmd->args, ft_lstnew(txtcopy(new, NULL, qtxt)));
		if (head->qtxt != qtxt)
			ft_lstclear(&qtxt, &free);
		words = words->next;
	}
}
