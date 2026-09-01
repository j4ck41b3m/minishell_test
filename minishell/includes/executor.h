#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

void	executor(t_shell *shell);
void	exec_cmd(t_shell *msh);
char	*get_cmd_path(char *cmd, t_env *env);
void	next_cmd(t_shell *msh);
char	**env_to_array(t_shell *msh);
int		fill_redirs(t_shell *shell, t_cmd *mycmd);
int		input_asignment(t_redir *tmp);
void	handle_status(t_shell *msh);
void	apply_redirs(t_cmd *cmd);
void	execve_cmd(t_shell *shell, t_cmd *cmd);
#endif
