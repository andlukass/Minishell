/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:24:50 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/30 19:51:54 by llopes-d         ###   ########.fr       */
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

static int	check_arguments(char **cmd, long *status)
{
	if (!cmd)
		return (1);
	printf("exit\n");
	*status = 2;
	if ((ft_strlen(cmd[1]) > 19 || !is_str_numeric(cmd[1])))
		return(print_error("", "numeric argument required\n"), 1);
	else if (cmd[1] && cmd[2])
	{
		print_error("", "too many arguments\n");
		if ((ft_strlen(cmd[1]) < 20 && is_str_numeric(cmd[1])))
			return (0);
		return (1);
	}
	else
	{
		if (cmd[1])
			*status = atoi(cmd[1]);
		else
			*status = 0;
		return (1);
	}
}

void	ft_exit(char **command, long status)
{
	int	must_exit;

	must_exit = check_arguments(command, &status);
	if (!must_exit)
	{
		get_data()->exit_status = 256;
		return ;
	}
	free_env(get_data()->env);
	if (get_data()->commands)
		free_commands(get_data()->commands);
	free(get_data()->prompt_color);
	rl_clear_history();
	exit(status);
}
