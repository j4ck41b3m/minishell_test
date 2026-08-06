#include "minishell.h"
#include "libft.h"

void	classify_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	aux = *cmd;
	while (aux)
	{
		if (aux->argc == 0)
			aux->is_builtin = 0;
		else
			aux->is_builtin = is_builtin(aux);
		aux = aux->next;
	}
}

t_status	prepare_redirections(t_shell *shell)
{
	t_cmd	*mycmd;

	mycmd = shell->cmd;
	while (mycmd)
	{
		fill_redirs(mycmd);
		mycmd = mycmd->next;
	}
	if (shell->cmd->next)
	{
		connect_pipes(&shell->cmd);
	}
	return (SUCCESS);
}

void	execute_single(t_shell *shell)
{
	if (shell->cmd->is_builtin)
	{
		exec_builtin(shell);
		return ;
	}
	else
		exec_cmd(shell);
	return ;
}

void	execute_pipeline(t_shell *shell)
{
	pid_t	pid;

	while (shell->cmd)
	{
		/* if (ft_isascii(shell->cmd->arg[0][0]) == 0)
		{
			shell->last_status = 1;
			break ;
		} */
		if (shell->cmd->is_builtin)
			exec_builtin(shell);
		else
		{
			g_signal = S_CMD;
			pid = fork();
			if (pid == 0)
				execute_single(shell);
			else
				waitpid(pid, &shell->last_status, 0);
			handle_status(shell);
		}
		next_cmd(shell);
	}
}

void	executor(t_shell *shell)
{
	if (!prepare_redirections(shell))
		return ;
	classify_cmd(&shell->cmd);
	/* if (!shell->cmd->next)
	{
		g_signal = S_CMD;
		execute_single(shell);
		handle_status(shell);
		while (shell->cmd->redirs)
		{
			if (shell->cmd->redirs->redir_in != 0)
				close(shell->cmd->redirs->redir_in);
			if (shell->cmd->redirs->redir_out != 1)
				close(shell->cmd->redirs->redir_out);
			shell->cmd->redirs = shell->cmd->redirs->next;
		}
	}
	else
	{
	} */
	execute_pipeline(shell);
}
