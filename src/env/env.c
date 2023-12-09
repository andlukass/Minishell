/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/09 15:00:10 by user             ###   ########.fr       */
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
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
	free(current->key);
	free(current->value);
	free(current);
}

t_env	*create_new_value(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_next_node(t_env **list, t_env *new)
{
	t_env	*current;

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
	t_env	*current;

	current = get_data()->env;
	if (get_data()->env)
	{
		while (current->next)
		{
			if (!strcmp(current->key, key))
				return (current->value);
			current = current->next;
		}
		return (NULL);
	}
	else
		return (NULL);
}

void	get_env(char *env[])
{
	int	index;
	char *key;
	char *value;

	index = 0;
	while (env[index])
	{
		key = strndup(env[index], strrchr(env[index], '=') - env[index]);
		if (!strcmp(key, "SHLVL"))
			value = ft_itoa( atoi(strrchr(env[index], '=') + 1) + 1);
		else
			value = strdup(strrchr(env[index], '=') + 1);
		add_next_node(&get_data()->env, create_new_value(key, value));
		index++;
	}
}
