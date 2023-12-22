/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:58:58 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 14:54:55 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **command)
{
	int	i;

	if (strcmp(command[1], "-n"))
		i = 1;
	else
		i = 2;
	while (command[i])
	{
		printf("%s", command[i++]);
		if (command[i])
			printf(" ");
	}
	if (strcmp(command[1], "-n"))
		printf("\n");
	exit (0);
}
