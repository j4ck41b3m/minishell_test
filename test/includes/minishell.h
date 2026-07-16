/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:50:10 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/07 12:41:06 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "libft.h"
# define MINISHELL_H

extern int	g_signal;

# define READLINE_MSG "\033[1;36mminishell\033[34m$> \033[0m"
# define HEREDOC_MSG "\033[1;34m> \033[0m" // @return >

typedef enum e_signal
{
	S_BASE, // señal Base
	S_HEREDOC, // entra en el heredoc
	S_HEREDOC_END, // finalización del heredoc
	S_SIGINT, // Ctrl + C
	S_SIGINT_CMD, // Ctrl + C en medio de una comando
	S_CMD, // se ejecuta un comando
	S_CANCEL_EXEC, // Ctrl + D en heredoc
	S_SIZE
}			t_signal;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}					t_env;

typedef enum e_redir_type
{
	TRUNC,
	INPUT,
	APPEND,
	HEREDOC,
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**arg;
	int				argc;
	char			*cmd_path;
	t_redir			*redirs;
	int				is_builtin;
	struct s_cmd	*next;
}					t_cmd;

typedef enum e_token_type
{
	WORD,
	TRUNC,
	INPUT,
	APPEND,
	HEREDOC,
	PIPE,
	EMPTY,
	CMD,
	ARG,
	END
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmd;
	int		last_status;
	int		running;
}			t_shell;
#endif
