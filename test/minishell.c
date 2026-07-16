/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 11:23:22 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/07 13:24:45 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_env_init(t_env **env, char **envp)
{
	t_env	*new;
	int		i;
	char	*var_name;
	char	*var_value;

	new = NULL;
	i = -1;
	while (++i < ft_arraylen(envp))
	{
		var_name = get_env_name(envp[i]);
		var_value = get_env_value(envp[i]);
		new = ft_lstnew_env(var_name, var_value, 1);
		ft_lstadd_back_env(env, new);
		ft_memfree(var_name);
		ft_memfree(var_value);
	}
}

static void	ft_minishell(t_shell *msh, char **envp)
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
