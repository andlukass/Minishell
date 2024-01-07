/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:04:04 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/07 19:54:04 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_quotes(char *command, int index, char quote_type)
{
	while (index >= 0 && command[index] != quote_type)
		index--;
	return (index);
}

static int	find_reds(char *command, int index, char c)
{
	char	quote_type;

	while (index >= 0)
	{
		if ((command[index] == '"' || command[index] == '\''))
		{
			quote_type = command[index--];
			index = skip_quotes(command, index, quote_type);
		}
		else if (command[index] == c)
			return (index);
		index--;
	}
	return (-1);
}

char	*get_last_redirection(char *command, char c)
{
	char	*reds;
	int		i;
	int		j;

	reds = malloc(sizeof(char) * 3);
	if (!reds)
		return (NULL);
	j = ft_strlen(command) - 1;
	i = find_reds(command, j, c);
	j = 0;
	if (i != -1)
	{
		reds[j++] = command[i];
		if (i > 0 && (command[i - 1] == '>' || command[i - 1] == '<'))
			reds[j++] = command[i - 1];
		reds[j] = '\0';
		if (ft_strlen(reds) == 1 || ft_strlen(reds) == 2)
			return (reds);
	}
	return (free(reds), NULL);
}
