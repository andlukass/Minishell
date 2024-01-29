/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:04:04 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/29 09:24:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_greater_than(char **command)
{
	char	**grater_than;
	int		index;
	int		size;

	index = 0;
	size = 0;
	while (command[index])
		if (command[index++][0] == '\6')
			size++;
	if (!size)
		return (NULL);
	grater_than = malloc(sizeof(char *) * (size + 1));
	if (!grater_than)
		ft_exit(NULL, 0);
	grater_than[size] = NULL;
	size = 0;
	index = 0;
	while (command[index])
	{
		if (command[index][0] == '\6')
			grater_than[size++] = ft_strdup(command[index]);
		index++;
	}
	return (grater_than);
}

char	*get_less_than(char **command)
{
	char	*less_than;
	int		index;

	less_than = NULL;
	index = 0;
	while (command[index])
	{
		if (command[index][0] == '\7')
		{
			if (less_than)
				free(less_than);
			less_than = ft_strdup(command[index]);
		}
		index++;
	}
	return (less_than);
}
