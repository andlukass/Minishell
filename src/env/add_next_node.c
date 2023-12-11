/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_next_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 22:21:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Create a new allocated node for t_env
 */
static t_env	*create_new_value(char *variable)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->variable = variable;
	new->next = NULL;
	return (new);
}

int	add_next_node(t_env **list, char *variable)
{
	t_env	*current;
	char	*env_key;
	char	*new_key;

	if (!(*(list)))
		return (*(list) = create_new_value(variable), 0);
	current = *(list);
	new_key = get_env_key(variable);
	while (current->next)
	{
		env_key = get_env_key(current->variable);
		if (!strcmp(new_key, env_key))
		{
			free(new_key);
			free(env_key);
			if (!ft_strchr(variable, '='))
				return (free(variable), 0);
			free(current->variable);
			return (current->variable = variable, 1);
		}
		free(env_key);
		current = current->next;
	}
	current->next = create_new_value(variable);
	free(new_key);
}
