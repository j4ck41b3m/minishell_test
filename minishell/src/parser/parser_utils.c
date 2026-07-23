#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints a syntax error in standar error
 *
 * @param token The token of the error
 */
void	print_syntax_error(t_token *token)
{
	if (!token)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline`",
			2);
	else if (!token->value)
	{
		if (token->type == PIPE)
			ft_putstr_fd("minishell: syntax error near unexpected token `|`", 2);
		else if (token->type == INPUT)
			ft_putstr_fd("minishell: syntax error near unexpected token `<`", 2);
		else if (token->type == TRUNC)
			ft_putstr_fd("minishell: syntax error near unexpected token `>`", 2);
		else if (token->type == APPEND)
			ft_putstr_fd("minishell: syntax error near unexpected token `>>`", 2);
		else if (token->type == HEREDOC)
			ft_putstr_fd("minishell: syntax error near unexpected token `<<`", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putendl_fd(token->value, 2);
	}
}
