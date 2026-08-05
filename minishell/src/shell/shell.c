#include "libft.h"
#include "minishell.h"

static void	update_shellevel(t_shell *shell)
{
	char	*shlvl;
	int	new_value;

	shlvl = env_get(shell->env, "SHLVL");
	if (!shlvl)
	{
		add_env(&shell->env, new_env("SHLVL", "1"));
		return ;
	}
	else
	{
		new_value = ft_atoi(shlvl);
		free(shlvl);
		if (new_value < 0)
			new_value = 0;
		new_value++;
		shlvl = ft_itoa(new_value);
		env_set(&shell->env, "SHLVL", shlvl);
		free(shlvl);
	}
}

static void	basic_env_vars(t_shell *shell)
{
	if (env_get(shell->env, "OLDPWD") == NULL)
		env_set(&shell->env, "OLDPWD", NULL);
	if (env_get(shell->env, "PWD") == NULL)
		env_set(&shell->env, "PWD", getcwd(NULL, 0));
	if (env_get(shell->env, "MAIL") == NULL)
		env_set(&shell->env, "MAIL", "bconejo-@student.42malaga.com");
	if (env_get(shell->env, "_") == NULL)
		env_set(&shell->env, "_", "/usr/bin/env");
	if (env_get(shell->env, "PS1") == NULL)
		env_set(&shell->env, "PS1", "\033[38;5;229mminishell \033[0m% \033[37m");
	update_shellevel(shell);
	return ;
}

/**
 * @brief Initializes a shell struct
 *
 * @param shell A pointer to the shell struct
 * @param envp The system environment variables
 * @return The prompt of the shell
 */
void	init_shell(t_shell *shell, char **envp, char **av)
{
	char	*tmp;

	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->name = av[0];
	shell->line = NULL;
	shell->last_status = 0;
	shell->running = 1;
	env_init(&shell->env, envp);
	tmp = env_get(shell->env, "PS1");
	if (!tmp)
	{
		add_env(&shell->env, new_env("PS1",
				"\033[38;5;229mminishell \033[0m% \033[37m"));
	}
	else
		free(tmp);
	basic_env_vars(shell);	
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to %s!\n", shell->name+2);
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
