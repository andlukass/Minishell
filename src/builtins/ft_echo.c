/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:58:58 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/30 21:21:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **command)
{
	int	i;
	int	has_flag;

	i = 1;
	has_flag = 0;
	if (command[1])
	{
		if (command[1][0] == '-' && command[1][1] != ' ' && ++i && ++has_flag)
		{
			if (ft_strcmp(&command[1][1], "n"))
			{
				printf("echo has only the '-n' flag\n");
				ft_exit(NULL);
			}
		}
		while (command[i])
		{
			printf("%s", command[i++]);
			if (command[i])
				printf(" ");
		}
	}
	if (!has_flag)
		printf("\n");
	ft_exit(NULL);
}
