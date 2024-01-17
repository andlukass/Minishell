/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:58:58 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/17 22:40:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	have_flag(char *str)
{
	int	index;

	index = 1;
	if (!str || str[0] != '-')
		return (0);
	while (str[index])
	{
		if (str[index] != 'n')
			return (0);
		index++;
	}
	return (1);
}

void	ft_echo(char **command)
{
	int	i;
	int	has_flag;

	has_flag = 0;
	i = 1;
	if (have_flag(command[1]) && ++has_flag)
		i = 2;
	while (command[i])
	{
		printf("%s", command[i++]);
		if (command[i])
			printf(" ");
	}
	if (!has_flag)
		printf("\n");
	ft_exit(NULL, 0);
}
