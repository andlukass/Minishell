/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:01:20 by user              #+#    #+#             */
/*   Updated: 2024/01/01 11:53:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_array(void)
{
	t_env	*current;
	char	**array;
	int		index;

	index = 0;
	current = get_data()->env;
	while (current && ++index)
		current = current->next;
	array = malloc(sizeof(char *) * (index + 1));
	current = get_data()->env;
	index = 0;
	while (current)
	{
		array[index++] = ft_strdup(current->variable);
		current = current->next;
	}
	array[index] = NULL;
	return (array);
}
