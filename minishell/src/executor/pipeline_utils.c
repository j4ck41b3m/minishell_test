#include "minishell.h"

void	handle_status(t_shell *msh)
{
	if (WIFEXITED(msh->last_status))
		msh->last_status = WEXITSTATUS(msh->last_status);
	if (msh && msh->last_status == 127)
		printf("%s: %s\n", msh->cmd->arg[0], "command not found");
	if (g_signal == S_SIGINT_CMD)
		msh->last_status = 130;
	g_signal = S_BASE;
}

void	next_cmd(t_shell *msh)
{
	t_cmd	*mycmd;

	free_cmd(&msh->cmd);
	if (msh->cmd->redirs->type != 0)
		close(msh->cmd->redirs->type);
	if (msh->cmd->redirs->type != 1)
		close(msh->cmd->redirs->type);
	mycmd = msh->cmd;
	msh->cmd = msh->cmd->next;
	free_mem(mycmd);
}
