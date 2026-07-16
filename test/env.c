/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 12:53:04 by jcolina-          #+#    #+#             */
/*   Updated: 2026/07/02 12:53:37 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_shell *myshell)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 0;
	tmp = myshell->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = myshell->env;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->key, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value);
		ft_memfree(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

char	*get_env_name(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

char	*get_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	if (fullenv[i + 1] == '\"')
		return (ft_substr(fullenv, i + 2, ft_strlen(fullenv) - i));
	else
		return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}

t_env	*ft_lstnew_env(char *name, char *value, int alloc)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	new_node->key = name;
	new_node->value = value;
	if (alloc)
	{
		new_node->key = ft_strdup(name);
		new_node->value = ft_strdup(value);
		if (!new_node->key || !new_node->value)
		{
			ft_memfree(new_node->key);
			ft_memfree(new_node->value);
			ft_memfree(new_node);
			return (NULL);
		}
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
