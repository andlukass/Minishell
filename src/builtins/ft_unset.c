/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:19:38 by user              #+#    #+#             */
/*   Updated: 2023/12/10 15:13:49 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_from_env(t_env *cur, t_env *previous, char *key)
{
	char	*old_key;

	while(cur)
	{
		if (strrchr(cur->variable, '='))
			old_key = strndup(cur->variable, \
				strchr(cur->variable, '=') - cur->variable);
		else
			old_key = strndup(cur->variable, ft_strlen(cur->variable));
		if(!strcmp(key, old_key))
		{
			if (!previous)
				get_data()->env = cur->next;
			else
				previous->next = cur->next;
			free(cur->variable);
			free(cur);
			free(old_key);
			return ;
		}
		free(old_key);
		previous = cur;
		cur = cur->next;
	}
}

void	ft_unset(void)
{
	int	i;

	i = 1;
	while (get_data()->input_array[i])
		remove_from_env(get_data()->env, NULL, get_data()->input_array[i++]);
}
