#include "minishell.h"
#include "libft.h"

static void	clean_screen(t_shell *shell)
{
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to %s!\n", shell->name + 2);
}

int	inter_mini(t_shell shell)
{
	char	*prompt;

	clean_screen(&shell);
	prompt = env_get(shell.env, "PS1");
	shell.line = readline(prompt);
	free(prompt);
	while (shell.line && shell.running)
	{
		if (parse(shell.line, &shell))
		{
			if (g_signal != S_SIGINT_CMD)
				executor(&shell);
			free_cmd(&shell.cmd);
			g_signal = S_BASE;
			if (!shell.running)
			{
				free(shell.line);
				shell.line = NULL;
				break ;
			}
		}
		add_history(shell.line);
		free(shell.line);
		prompt = env_get(shell.env, "PS1");
		shell.line = readline(prompt);
		free(prompt);
	}
	end_shell(&shell);
	return (shell.last_status);
}

int	non_intermini(t_shell shell)
{
	shell.line = read_line();
	while (shell.line && shell.running)
	{
		if (parse(shell.line, &shell))
		{
			add_history(shell.line);
			if (g_signal != S_SIGINT_CMD)
				executor(&shell);
			free_cmd(&shell.cmd);
			g_signal = S_BASE;
		}
		free(shell.line);
		shell.line = read_line();
	}
	end_shell(&shell);
	return (shell.last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac > 1)
		return (1);
	init_shell(&shell, envp, av);
	if (isatty(STDIN_FILENO) == 0)
		return (non_intermini(shell));
	else
		return (inter_mini(shell));
}
