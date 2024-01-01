/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:24:50 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/01 13:00:30 by user             ###   ########.fr       */
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
	free_env(get_data()->env);
	free_commands(get_data()->commands);
	rl_clear_history();
	exit(0);
}
