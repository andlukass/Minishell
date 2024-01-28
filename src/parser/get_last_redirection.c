/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:04:04 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/28 18:34:14 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_last_redirection(char **command, char c)
{
	char	*reds;
	int		index;

	reds = NULL;
	index = 0;
	while (command[index])
	{
		if (command[index][0] == c)
		{
			if (reds)
				free(reds);
			reds = ft_strdup(command[index]);
		}
		index++;
	}
	return (reds);
}
