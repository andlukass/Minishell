/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:43 by user              #+#    #+#             */
/*   Updated: 2024/01/06 11:58:04 by user             ###   ########.fr       */
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
	new_command[j] = NULL;
	free(splitted);
	return (new_command);
}
