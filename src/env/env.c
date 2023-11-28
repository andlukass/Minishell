/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/28 20:24:49 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_new_value(char *str)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = strndup(str, strrchr(str, '=')- str);
	new->value = strdup(strrchr(str, '=')+1);
	new->next = NULL;
	return (new);
}

void	add_next_node(t_env *new)
{
	t_env *current;

	if(get_data()->env)
	{
		current = get_data()->env;
		while(current->next)
			current = current->next;
		current->next = new;
	}
	else
		get_data()->env = new;
}

void get_env(char *env[])
{
	int index;

	index = 0;
	while(env[index])
		add_next_node(create_new_value(env[index++]));
}