/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:34:52 by user              #+#    #+#             */
/*   Updated: 2024/01/28 19:44:33 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "\6") || \
		!ft_strcmp(str, "\6\6") || \
		!ft_strcmp(str, "\7") || \
		!ft_strcmp(str, "\7\7"))
		return (1);
	return (0);
}

static int	verify_redirections(char *new_input)
{
	int		index;
	char	**splitted;

	index = 0;
	splitted = ft_split(new_input, '\2');
	while (splitted[index])
	{
		if ((is_redirection(splitted[index]) && \
			!splitted[index + 1]) || \
			(is_redirection(splitted[index]) && \
			is_redirection(splitted[index + 1])))
			return (free_double_array(splitted), 0);
		index++;
	}
	return (free_double_array(splitted), 1);
}

static int	verify_pipes(char *new_input)
{
	char	**splitted;
	int		index;
	int		i;
	int		result;

	index = -1;
	result = 1;
	splitted = ft_split(new_input, '\2');
	while (splitted[++index])
	{
		i = -1;
		while (splitted[index][++i])
		{
			if (splitted[index][i] == '\3')
			{
				if (i == 0 && index == 0)
					result = 0;
				if (!splitted[index][i + 1] && !splitted[index + 1])
					result = 0;
				if (splitted[index][i + 1] == '\3')
					result = 0;
			}
		}
	}
	return (free_double_array(splitted), result);
}

static int	open_quotes(char *new_input)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (new_input[index])
	{
		if (new_input[index] == '\4')
			counter++;
		index++;
	}
	if (counter % 2 != 0)
		return (1);
	counter = 0;
	index = 0;
	while (new_input[index])
	{
		if (new_input[index] == '\5')
			counter++;
		index++;
	}
	if (counter % 2 != 0)
		return (1);
	return (0);
}

int	seek_errors(char *new_input)
{
	if (open_quotes(new_input))
		return (printf("there are unclosed quotes.\n"));
	if (!verify_pipes(new_input))
		return (printf("pipe syntax error.\n"));
	if (!verify_redirections(new_input))
		return (printf("redirection syntax error.\n"));
	return (0);
}
