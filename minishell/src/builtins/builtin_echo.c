#include "minishell.h"
#include "libft.h"

static t_status	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str && ft_strchr("-n", str[i]))
			i++;
		else
			return (FAILURE);
	}
	return (SUCCESS);
}



/**
 * @brief Echo the STRING(s) to standard output
 * 
 * @param msh The global status of minishell
 */
void	builtin_echo(t_shell *msh)
{
	int	i;
	int	test_arg;

	i = 1;
	test_arg = 1;
	msh->last_status = 0;
	while (msh->cmd->arg[i])
	{
		if (!ft_strncmp(msh->cmd->arg[i], "-n", 2))
		{
			if (check_arg(msh->cmd->arg[i]) && test_arg)
			{
				i++;
			}
			else
			{
				test_arg = 0;
				ft_putstr_fd(msh->cmd->arg[i++], 1);
				if (msh->cmd->arg[i])
					ft_putchar_fd(32, 1);
			}
		}
		else
		{
			while (msh->cmd->arg[i])
			{
				ft_putstr_fd(msh->cmd->arg[i++], 1);
				if (msh->cmd->arg[i])
					ft_putchar_fd(32, 1);
			}
		}
	}
	if (!(msh->cmd->arg[1] && !ft_strncmp(msh->cmd->arg[1], "-n", 2)))
		ft_putchar_fd(10, 1);
}
