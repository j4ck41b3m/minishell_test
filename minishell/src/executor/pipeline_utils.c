#include "minishell.h"
#include "libft.h"

void	handle_status(t_shell *msh)
{
	if (WIFEXITED(msh->last_status))
		msh->last_status = WEXITSTATUS(msh->last_status);
	if (msh && msh->last_status == 127)
		printf("%s: %s\n", msh->cmd->arg[0], "command not found");
	if (g_signal == S_SIGINT_CMD)
		msh->last_status = 130;
	printf("Status is %d\n", msh->last_status);
	g_signal = S_BASE;
}

void	next_cmd(t_shell *msh)
{
	t_cmd	*mycmd;

	mycmd = msh->cmd;
	while (mycmd->redirs)
	{
		if (mycmd->redirs->redir_in != 0)
			close(mycmd->redirs->redir_in);
		if (mycmd->redirs->redir_out != 1)
			close(mycmd->redirs->redir_out);
		mycmd->redirs = mycmd->redirs->next;
	}
	msh->cmd = msh->cmd->next;
}

/**
 * @brief Converts the list into an array
 *
 * This function converts the enviroment list into an array chain in a 
 * "key=value" form, where each array element rpresents an enviroment variable
 * The arrayś last element is NULL
 *
 * @param msh Shell pointer
 * @return Array chain that represents the enviroment variables
 * in the "key=value" format
 */
char	**env_to_array(t_shell *msh)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 1;
	tmp = msh->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = msh->env;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->key, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value);
		free_mem(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}