
#include "../inc/minishell.h"

static int	handle_single_builtin(t_shell *content, t_exec *tmp)
{
	if (err_redirs(tmp, content))//start from here for 1004
}

int	exec(t_shell *content)
{
	t_exec	*tmp;

	if (content->ct_exec == 0)
		return (0);
	set_std(content, 0);//create the function in exec_utils.c
	tmp = ctx->exec;
	if (ctx->ct_exec == 1)
	{
		if (tmp->cmd == NULL && tmp->redirs != NULL)
			return (handle_single_redir(content, tmp));//create the function
		if (chk_is_builtin(tmp->cmd))
			return (handle_sigle_builtin(content, tmp));
	}
	init_signal_exec();//added for signal
	exec_parent(content);
	return (0);
}
