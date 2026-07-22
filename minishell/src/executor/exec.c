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
	(void)shell;
	return (SUCCESS);
}

void	execute_single(t_shell *shell)
{
	classify_cmd(&shell->cmd);
	if (shell->cmd->is_builtin)
		ft_builtin(shell);
	else
		exec_cmd(shell);
	return ;
}

void	execute_pipeline(t_shell *shell)
{
	pid_t	pid;

	while (shell->cmd)
	{
		if (!ft_isascii(shell->cmd->arg[0][0]))
		{
			shell->last_status = 1;
			break ;
		}
		if (shell->cmd->is_builtin)
			ft_builtin(shell);
		else
		{
			g_signal = S_CMD;
			pid = fork();
			if (pid == 0)
				execute_single(shell);
			else
				waitpid(-1, &shell->last_status, 0);
			handle_status(shell);
		}
		next_cmd(shell);
	}
	return ;
}

void	executor(t_shell *shell)
{
	if (!shell->cmd)
	{
		printf("no command\n");
		return ;
	}
	if (!prepare_redirections(shell))
		return ;
	if (!shell->cmd->next)
		execute_single(shell);
	else
		execute_pipeline(shell);
}
