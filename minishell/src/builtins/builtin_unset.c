#include "minishell.h"

/**
 * @brief Unsets values of variables
 * 
 * @param shell The global status of minishell
 */
void	builtin_unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (i < shell->cmd->argc)
		env_unset(&shell->env, shell->cmd->arg[i++]);
}
