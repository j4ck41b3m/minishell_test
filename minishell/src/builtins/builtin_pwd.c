#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints the full filename of the current working directory
 * 
 * @param msh The global status of minishell
 */
void	builtin_pwd(t_shell *msh)
{
	char	*pwd;

	msh->last_status = 0;
	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
