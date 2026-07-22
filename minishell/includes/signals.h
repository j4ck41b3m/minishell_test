#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

/**
 * @enum e_signal
 * @brief Enum representing the signal types used for emulating
 * shell behaviour
*/
typedef enum e_signal
{
	S_BASE,			// Base signal
	S_HEREDOC,		// entering Heredoc
	S_HEREDOC_END,	// finishing Heredoc
	S_SIGINT,		// Ctrl + C
	S_SIGINT_CMD,	// Ctrl + C in the middle of a command
	S_CMD,			// comman executing
	S_CANCEL_EXEC,	// Ctrl + D in Heredoc
	S_SIZE
}			t_signal;

void	signal_init(void);
void	sigint_handler(int sig);
void	sigint_handler_aux(void);

#endif