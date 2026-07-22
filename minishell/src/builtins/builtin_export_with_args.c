#include "minishell.h"
#include "libft.h"

static void	error_key(t_shell *shell, int i)
{
	char		*tmp;
	char		*msg;
	char		*path;

	path = ft_strjoin(shell->cmd->arg[i], "': ");
	tmp = ft_strjoin("minishell: export: `", path);
	msg = ft_strjoin(tmp, "not a valid identifier");
	ft_putendl_fd(msg, 2);
	shell->last_status = 1;
	free_mem(path);
	free_mem(tmp);
	free_mem(msg);
}

static char	*get_key(t_shell *shell, int i, int *j)
{
	int	start;

	if (shell->cmd->arg[i][*j] == '=')
	{
		error_key(shell, i);
		return (NULL);
	}
	start = *j;
	while (shell->cmd->arg[i] && shell->cmd->arg[i][*j] != '='
		&& shell->cmd->arg[i][*j])
		(*j)++;
	return (ft_substr(shell->cmd->arg[i], start, *j - start));
}

static char	*get_value(char *str, int *i)
{
	int	start;

	if (str && str[*i] == '=')
		(*i)++;
	start = *i;
	while (str && str[*i])
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

void	export_with_args(t_shell *shell)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	key = NULL;
	i = 1;
	while (i < shell->cmd->argc)
	{
		j = 0;
		value = NULL;
		key = get_key(shell, i, &j);
		if (key)
			value = get_value(shell->cmd->arg[i], &j);
		if (value)
			env_set(&shell->env, key, value);
		free(key);
		free(value);
		i++;
	}

}
