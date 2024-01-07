/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:43 by user              #+#    #+#             */
/*   Updated: 2024/01/07 19:14:56 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redirection(char *str)
{
	if (!ft_strcmp(str, ">") || \
		!ft_strcmp(str, ">>") || \
		!ft_strcmp(str, "<") || \
		!ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

char	**get_command(char *command)
{
	char	**splitted;
	char	**new_command;
	int		index;
	int		j;

	j = 0;
	index = 0;
	splitted = ft_split(command, '\2');
	while (splitted[index])
		index++;
	new_command = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (splitted[index])
	{
		if (is_redirection(splitted[index]))
			index = index + 2;
		else
			new_command[j++] = splitted[index++];
	}
	if (!j)
		return (free(splitted), NULL);
	else
		new_command[j] = NULL;
	return (free(splitted), new_command);
}
