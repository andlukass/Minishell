/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:24:50 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/05 19:50:45 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **command)
{
	if (command)
	{
		if (command[1] != (void *)0)
		{
			printf("exit doesn't take any arguments!\n");
			return ;
		}
		printf("exit\n");
	}
	free(get_data()->username);
	free_env(get_data()->env);
	free_commands(get_data()->commands);
	rl_clear_history();
	exit(0);
}
