#include "minishell.h"
#include "libft.h"

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	char	*prompt;

	(void)av;
	if (ac == 1)
	{
		init_shell(&shell, envp);
		prompt = env_get(shell.env, "PS1");
		shell.line = readline(prompt);
		free(prompt);
		while (shell.line)
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
			prompt = env_get(shell.env, "PS1");
			shell.line = readline(prompt);
			free(prompt);
		}
		end_shell(&shell);
		return (0);
	}
	printf("Error!\n");
	return (1);
}
