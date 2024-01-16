/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:40:21 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/16 16:18:08 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **command)
{
	int	status;

	if (command[1] != (void *)0)
	{
		status = 1;
		printf("pwd doesn't take any arguments!\n");
	}
	else if (get_env_value("PWD"))
	{
		status = 0;
		printf("%s\n", get_env_value("PWD"));
	}
	else
	{
		status = 1;
		printf("PWD is not set!\n");
	}
	ft_exit(NULL, status);
}
