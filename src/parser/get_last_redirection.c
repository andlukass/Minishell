/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:04:04 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/07 14:38:15 by isbraz-d         ###   ########.fr       */
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
	int		index;
	int		i;
	int		j;

	reds = malloc(sizeof(char) * 3);
	if (!reds)
		return (NULL);
	i = ft_strlen(command) - 1;
	j = 0;
	index = find_reds(command, i, c);
	if (index != -1)
	{
		reds[j++] = command[index];
		if (command[index - 1] == '>' || command[index - 1] == '<')
			reds[j++] = command[index - 1];
		reds[j] = '\0';
		if (ft_strlen(reds) == 1 || ft_strlen(reds) == 2)
			return (reds);
	}
	return (free(reds), NULL);
}
