#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

void	executor(t_shell *shell);
void	exec_cmd(t_shell *msh);
char	*get_cmd_path(char *cmd, t_env *env);
void	next_cmd(t_shell *msh);
void	handle_status(t_shell *msh);

#endif