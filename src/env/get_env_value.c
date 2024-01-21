/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/21 14:22:48 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *key)
{
	t_env	*current;
	char	*env_key;

	if (!key)
		return ((void *)0);
	current = get_data()->env;
	if (get_data()->env)
	{
		while (current)
		{
			env_key = get_env_key(current->variable);
			if (!ft_strcmp(env_key, key))
			{
				free(env_key);
				if (!ft_strchr(current->variable, '='))
					return ((void *)0);
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
