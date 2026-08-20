#include "minishell.h"
#include "libft.h"

static void	clearScreen(t_shell *shell)
{
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to %s!\n", shell->name + 2);
}

int	inter_mini(t_shell shell)
{
	char	*prompt;

	clearScreen(&shell);
	prompt = env_get(shell.env, "PS1");
	shell.line = readline(prompt);
	free(prompt);
	while (shell.line && shell.running)
	{
		if (parse(shell.line, &shell))
		{
			printf("THE LINE IS: %s\n", shell.line);
			add_history(shell.line);
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
		free(shell.line);
		prompt = env_get(shell.env, "PS1");
		shell.line = readline(prompt);
		free(prompt);
	}
	end_shell(&shell);
	return (0);
	printf("Error!\n");
	return (1);
}

int	non_intermini(t_shell shell, char **args, int count)
{
	shell.line = fuseargs(args, count);
	if (parse(shell.line, &shell))
	{
		add_history(shell.line);
		if (g_signal != S_SIGINT_CMD)
			executor(&shell);
		free_cmd(&shell.cmd);
		g_signal = S_BASE;
	}
	end_shell(&shell);
	return (0);
	printf("Error!\n");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	init_shell(&shell, envp, av);
	if (ac > 1)
		return (non_intermini(shell, av, ac));
	else
		return (inter_mini(shell));
}
