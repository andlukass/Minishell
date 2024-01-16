/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:24:50 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/16 16:39:13 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **command, int status)
{
	if (command)
	{
		if (command[1] != (void *)0)
		{
			printf("exit doesn't take any arguments!\n");
			get_data()->exit_status = 1;
			return ;
		}
		printf("exit\n");
	}
	free_env(get_data()->env);
	if (get_data()->commands)
		free_commands(get_data()->commands);
	rl_clear_history();
	exit(status);
}
