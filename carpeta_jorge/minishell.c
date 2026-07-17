/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:23:22 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/16 19:32:23 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_env_init(t_env **env, char **envp)
{
	t_env	*new;
	int		i;
	char	*key;
	char	*var_value;

	new = NULL;
	i = -1;
	while (++i < ft_arraylen(envp))
	{
		key = get_env_name(envp[i]);
		var_value = get_env_value(envp[i]);
		new = ft_lstnew_env(key, var_value, 1);
		ft_lstadd_back_env(env, new);
		ft_memfree(key);
		ft_memfree(var_value);
	}
}

void	ft_minishell(t_shell *msh, char **envp)
{
	char	*input;
	char	*tmp;

	ft_lst_env_init(&msh->env, envp);
	while (1)
	{
		if (g_signal == S_SIGINT)
			msh->last_status = 1;
		input = readline(READLINE_MSG);
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		if (!input)
			break ;
		if (tmp[0] != 0)
			add_history(tmp);
		ft_prev_exec(tmp, msh);
		if (g_signal != S_CANCEL_EXEC)
			ft_executor(msh, envp);
		ft_clean_shell(tmp, input, msh);
		g_signal = S_BASE;
	}
	ft_free_list(&msh->env);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	myshell;

	if (ac != 1 || av[1])
		return (1);
	signal_init();
	ft_minishell(&myshell, envp);
	return (0);
}
