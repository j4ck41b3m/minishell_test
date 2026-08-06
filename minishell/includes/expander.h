#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"

char	*extract_single_quoted(char *value, int *i);
char	*extract_double_quoted(char *value, int *i, t_env *env,
			int last_status);
char	*expand_tilde(int *i, t_env *env);
char	*expand_variable(char *value, int *i, t_env *env, int last_status);
char	*extract_plain_text(char *value, int *i);
void	expand_tokens(t_token **list, t_env *env, int last_status);

#endif