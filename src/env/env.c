/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 14:55:05 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *stack)
{
	t_env	*current;
	t_env	*temp;

	current = stack;
	while (current->next)
	{
		temp = current->next;
		free(current->variable);
		free(current);
		current = temp;
	}
	free(current->variable);
	free(current);
}

t_env	*create_new_value(char *variable)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->variable = variable;
	new->next = NULL;
	return (new);
}

void	add_next_node(t_env **list, t_env *new)
{
	t_env	*current;
	char	*old_key;

	if (*(list))
	{
		current = *(list);
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		*(list) = new;
}

char	*get_env_value(char *key)
{
	t_env	*cur;
	char	*old_key;

	cur = get_data()->env;
	if (get_data()->env)
	{
		while (cur->next)
		{
			if (strrchr(cur->variable, '='))
				old_key = strndup(cur->variable, \
					strrchr(cur->variable, '=') - cur->variable);
			else
				old_key = strndup(cur->variable, ft_strlen(cur->variable));
			if (!strcmp(old_key, key))
			{
				free(old_key);
				return (strrchr(cur->variable, '=') + 1);
			}
			free(old_key);
			cur = cur->next;
		}
		return (NULL);
	}
	else
		return (NULL);
}

void	get_env(char *env[])
{
	int		index;
	char	*variable;
	char	*level;

	index = 0;
	while (env[index])
	{
		if (!strncmp(env[index], "SHLVL", 5))
		{
			level = ft_itoa(atoi(&env[index][6]) + 1);
			variable = ft_strjoin("SHLVL=", level, NO_FREE);
			free(level);
		}
		else
			variable = strndup(env[index], ft_strlen(env[index]));
		add_next_node(&get_data()->env, create_new_value(variable));
		index++;
	}
}
