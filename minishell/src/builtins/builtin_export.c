#include "minishell.h"
#include "builtins_utils.h"

void	builtin_export(t_shell *shell)
{
	shell->last_status = 0;
	if (shell->cmd->argc == 1)
		export_no_args(shell);
	else
		export_with_args(shell);
}
