#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks the arguments of the exit command
 * 
 * @param msh The global status of minishell
 * @return The error code corresponding to the number of arguments 
 * 
 * - 0 if no error
 * 
 * - 1 if the number of arguments is greater than one 
 * 
 * - 2 if is not an numeric argument 
 * 
 * - the number passed by argument
 */
static int	check_exit_args(t_shell *msh)
{
	int	i;

	if (msh->cmd->argc > 2)
		return (1);
	if (msh->cmd->arg[1])
	{
		i = -1;
		while (msh->cmd->arg[1][++i])
		{
			if (!ft_isdigit(msh->cmd->arg[1][i]))
			{
				printf("exit: %s: numeric argument required\n",
					msh->cmd->arg[1]);
				return (2);
			}
		}
		return (ft_atoi(msh->cmd->arg[1]));
	}
	return (0);
}

/**
 * @brief Causes the shell to exit from its current execution environment
 * 
 * @param msh The global status of minishell
 */
void	builtin_exit(t_shell *msh)
{
	ft_putendl_fd("exit", 2);
	msh->last_status = check_exit_args(msh);
	if (msh->last_status == 0)
		exit(msh->last_status);
	ft_putendl_fd("exit: too many arguments", 2);
}
