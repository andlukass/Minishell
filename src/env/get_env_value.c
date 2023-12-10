/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 22:22:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
