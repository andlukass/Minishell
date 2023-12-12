/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 23:47:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *key)
{
	t_env	*current;
	char	*env_key;

	current = get_data()->env;
	if (get_data()->env)
	{
		while (current)
		{
			env_key = get_env_key(current->variable);
			if (!strcmp(env_key, key))
			{
				free(env_key);
				return (ft_strchr(current->variable, '=') + 1);
			}
			free(env_key);
			current = current->next;
		}
		return ((void *)0);
	}
	else
		return ((void *)0);
}
