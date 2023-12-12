/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 23:58:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_value(char *key)
{
	t_env	*current;
	t_env	*previous;
	char	*env_key;

	current = get_data()->env;
	previous = (void *)0;
	while (current)
	{
		env_key = get_env_key(current->variable);
		if (!strcmp(key, env_key))
		{
			if (!previous)
				get_data()->env = current->next;
			else
				previous->next = current->next;
			free(current->variable);
			free(current);
			free(env_key);
			return ;
		}
		free(env_key);
		previous = current;
		current = current->next;
	}
}
