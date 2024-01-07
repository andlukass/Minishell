/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:43 by user              #+#    #+#             */
/*   Updated: 2024/01/07 19:45:25 by llopes-d         ###   ########.fr       */
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

char	**get_command(char **command)
{
	char	**new_command;
	int		index;
	int		j;

	j = 0;
	index = 0;
	while (command[index])
		index++;
	new_command = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (command[index])
	{
		if (is_redirection(command[index]))
			index = index + 2;
		else
			new_command[j++] = ft_strdup(command[index++]);
	}
	if (!j)
		return (free(new_command), NULL);
	else
		new_command[j] = NULL;
	return (new_command);
}
