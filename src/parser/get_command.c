/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:43 by user              #+#    #+#             */
/*   Updated: 2024/02/01 17:25:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (is_redirection(command[index]) && command[index + 1])
			index = index + 2;
		else if (is_redirection(command[index]) && !command[index + 1])
			index++;
		else
			new_command[j++] = ft_strdup(command[index++]);
	}
	if (!j)
		return (free(new_command), NULL);
	else
		new_command[j] = NULL;
	return (new_command);
}
