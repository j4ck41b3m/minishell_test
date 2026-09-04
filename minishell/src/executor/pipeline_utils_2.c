/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:32:07 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:32:10 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Iterates through all commands and closes their opened FDs
 * 
 * @param shell The global status of minishell
 */
void	close_pids(t_shell *shell)
{
	t_redir	*redir;
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->redir_in > 2)
				close(redir->redir_in);
			if (redir->redir_out > 2)
				close(redir->redir_out);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Waits for pipeline children and sets the global exit status
 * 
 * @param shell The global status of minishell
 * @param last_pid The PID of the last command executed in the pipeline
 */
void	exec_pipeline_cont(t_shell *shell, pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
	else
		shell->last_status = 1;
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	close_pids(shell);
}
