/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:19:38 by user              #+#    #+#             */
/*   Updated: 2023/12/10 14:49:58 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_from_env(char *key)
{
	t_env	*current;
	t_env	*previous;
	char	*old_key;

	current = get_data()->env;
	previous = NULL;
	while(current)
	{
		if (strrchr(current->variable, '='))
				old_key = strndup(current->variable, \
					strchr(current->variable, '=') - current->variable);
			else
				old_key = strndup(current->variable, ft_strlen(current->variable));
		if(!strcmp(key, old_key))
		{
			if (!previous)
				get_data()->env = current->next;
			else
				previous->next = current->next;
			free(current->variable);
			free(current);
		}
		free(old_key);
		previous = current;
		current = current->next;
	}
}

void	ft_unset(void)
{
	int	i;

	i = 1;
	while (get_data()->input_array[i])
		remove_from_env(get_data()->input_array[i++]);
}
