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

	if (msh->cmd->arg[1])
	{
		i = 0;
		if (msh->cmd->arg[1][i] == '-' || msh->cmd->arg[1][i] == '+'
			|| ft_isdigit(msh->cmd->arg[1][i]))
			i++;
		while (msh->cmd->arg[1][i])
		{
			if (!ft_isdigit(msh->cmd->arg[1][i]))
			return (2);
			i++;
		}
		if (msh->cmd->argc > 2)
			return (1);
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
	char	*tmp;
	char	*msg;

	ft_putendl_fd("exit", 2);
	msh->last_status = check_exit_args(msh);
	if (msh->last_status == 1)
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	else if (msh->last_status == 2)
	{
		tmp = ft_strjoin("minishell: exit: ", msh->cmd->arg[1]);
		msg = ft_strjoin(tmp, ": numeric argument required");
		free(tmp);
		ft_putendl_fd(msg, 2);
		free(msg);
		msh->running = 0;
//		end_shell(msh);
//		exit(msh->last_status);
	}
	else
	{
		msh->running = 0;
//		end_shell(msh);	
//		exit(msh->last_status);
	}
}
