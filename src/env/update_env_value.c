/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 22:22:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_value(char *key, char *variable)
{
	t_env	*current;
	char	*env_key;

	current = get_data()->env;
	if (get_data()->env)
	{
		while (current->next)
		{
			env_key = get_env_key(current->variable);
			if (!strcmp(env_key, key))
			{
				free(env_key);
				free(current->variable);
				current->variable = variable;
				return ;
			}
			free(env_key);
			current = current->next;
		}
	}
}
