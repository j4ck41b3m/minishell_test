#include "libft.h"
#include "minishell.h"

/**
 * @brief Initializes a shell struct
 *
 * @param shell A pointer to the shell struct
 * @param envp The system environment variables
 * @return The prompt of the shell
 */
void	init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->line = NULL;
	shell->last_status = 0;
	shell->running = 1;
	env_init(&shell->env, envp);
	add_env(&shell->env, new_env("PS1",
			"\033[38;5;229mminishell \033[0m% \033[37m"));
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to minishell!\n");
	signal_init();
}

/**
 * @brief Frees the memory space occupied by environment and command list
 *
 * @param shell A pointer to the shell struct
 */
void	end_shell(t_shell *shell)
{
	free(shell->line);
	free_env(&shell->env);
	free_cmd(&shell->cmd);
	rl_clear_history();
}
