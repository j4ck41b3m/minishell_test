/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:58:39 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/16 19:26:08 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sig);
static void	sigint_handler_aux(void);

/**
 * @brief Initializes the shell's signal handling
 *
 * This function Initializes the shell's signal handling, estalishing the
 * signal handlers for SIGINT and SIGQUIT. It also initializes the
 * g_signal variable
 */
void	signal_init(void)
{
	g_signal = S_BASE;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Signal handler for SIGINT y SIGQUIT.
 *
 * This function handles de SIGINT and SIGQUIT signals. Depending on the actual
 * state of g_signal, it does specific actions like interrupting a command
 * exectuion, canceling an execution command, or finalizing a heredoc.
 *
 * @param sig is the recieved signal's number
 */
static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == S_BASE || g_signal == S_SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_signal == S_CMD)
	{
		g_signal = S_SIGINT_CMD;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
	}
	else if (g_signal == S_HEREDOC)
	{
		ioctl(0, TIOCSTI, '\n');
		exit(0);
	}
	sigint_handler_aux();
}

/**
 * @brief Auxiliary function for the purpose of handling additional SIGINT cases.
 *
 * This function manages additional SIGINT cases not directly covered by the main
 * handler. For examplem canceling a heredoc execution or stablishing the
 * S_SIGINT signal into base state or heredoc.
 */
static void	sigint_handler_aux(void)
{
	if (g_signal == S_HEREDOC_END)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_CANCEL_EXEC;
	}
	else if (g_signal == S_BASE || g_signal == S_HEREDOC)
		g_signal = S_SIGINT;
}
