/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:24:50 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/17 22:40:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_str_numeric(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (1);
	if (str[index] == '-' || str[index] == '+')
		index++;
	while (str[index])
	{
		if (str[index] < '0' || str[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

static int	check_arguments(char **command, long *status)
{
	if (!command)
		return (1);
	if (ft_strlen(command[1]) > 19 || !is_str_numeric(command[1]))
	{
		get_data()->exit_status = 512;
		printf("exit: numeric argument required\n");
		return (0);
	}
	else if (command[1] && command[2])
	{
		get_data()->exit_status = 256;
		printf("exit: too many arguments\n");
		return (0);
	}
	else
	{
		if (command[1])
			*status = atoi(command[1]);
		else
			*status = 0;
		printf("exit\n");
		return (1);
	}
}

void	ft_exit(char **command, long status)
{
	int	must_exit;

	must_exit = check_arguments(command, &status);
	if (!must_exit)
		return ;
	free_env(get_data()->env);
	if (get_data()->commands)
		free_commands(get_data()->commands);
	rl_clear_history();
	exit(status);
}
