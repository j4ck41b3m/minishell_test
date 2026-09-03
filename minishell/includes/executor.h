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
void	classify_cmd(t_cmd **cmd);
void	exec_split(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2]);
void	exec_split_second(t_cmd *cmd, int *prev_fd, int pipefd[2]);
void	exec_pipeline_cont(t_shell *shell, pid_t last_pid);
void	exit_pipecmd(t_shell *shell, char *str);
void	handle_status(t_shell *msh);
void	apply_redirs(t_cmd *cmd);
void	child_exec(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2]);
void	execve_cmd(t_shell *shell, t_cmd *cmd);
int		heredoc(t_shell *shell, char *limit);

#endif
