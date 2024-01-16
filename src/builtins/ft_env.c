/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:58:58 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/16 16:15:33 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char **command)
{
	t_env	*current;

	if (command[1])
	{
		printf("env doesn't take any arguments!\n");
		ft_exit(NULL, 1);
	}
	current = get_data()->env;
	while (current)
	{
		if (ft_strchr(current->variable, '='))
			printf("%s\n", current->variable);
		current = current->next;
	}
	ft_exit(NULL, 0);
}
