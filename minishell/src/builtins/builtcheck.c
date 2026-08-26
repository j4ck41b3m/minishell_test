#include "libft.h"
#include "minishell.h"

/**
 * @brief Checks if a command is builtin
 *
 * @param cmd The command to check
 * @return SUCCESS if is a builtin command, FAILURE otherwise
 */
t_status	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->arg[0], "echo") || !ft_strcmp(cmd->arg[0], "cd")
		|| !ft_strcmp(cmd->arg[0], "pwd") || !ft_strcmp(cmd->arg[0], "export")
		|| !ft_strcmp(cmd->arg[0], "unset") || !ft_strcmp(cmd->arg[0], "env")
		|| !ft_strcmp(cmd->arg[0], "exit"))
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Selects the builtin command to run
 *
 * @param shell The global status of minishell
 */
void	exec_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->arg[0], "echo"))
		builtin_echo(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "cd"))
		builtin_cd(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "pwd"))
		builtin_pwd(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "export"))
		builtin_export(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "unset"))
		builtin_unset(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "env"))
		builtin_env(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "exit"))
		builtin_exit(shell);
}

static int	is_space(int c)
{
	return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32);
}

long	ft_atol(const char *str)
{
	long	result;
	long	sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}
