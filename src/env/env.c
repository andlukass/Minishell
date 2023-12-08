/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/08 14:54:15 by llopes-d         ###   ########.fr       */
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

t_env	*create_new_value(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = strndup(str, strrchr(str, '=') - str);
	if (!strcmp(new->key, "SHLVL"))
		new->value = ft_itoa( atoi(strrchr(str, '=') + 1) + 1);
	else
		new->value = strdup(strrchr(str, '=') + 1);
	new->next = NULL;
	return (new);
}

void	add_next_node(t_env *new)
{
	t_env	*current;

	if (get_data()->env)
	{
		current = get_data()->env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		get_data()->env = new;
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

	index = 0;
	while (env[index])
		add_next_node(create_new_value(env[index++]));
}
