/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:58:58 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 19:21:50 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(void)
{
	t_env	*current;

	if (get_data()->input_array[1])
	{
		printf("env doesn't take any arguments!\n");
		return ;
	}
	current = get_data()->env;
	while (current)
	{
		if (ft_strchr(current->variable, '='))
			printf("%s\n", current->variable);
		current = current->next;
	}
}
