/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:34:52 by user              #+#    #+#             */
/*   Updated: 2024/01/29 15:57:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Verify if the input have no redirect errors.
 * @param new_input string with the user input, already changed with the
 * specials characters.
 * @return 1 if it have the correct redirections, 0 if doesn't.
 */
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

/**
 * @brief	Verify if the input have no pipe errors.
 * @param new_input string with the user input, already changed with the
 * specials characters.
 * @return 1 if it have the correct pipes, 0 if doesn't.
 */
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

/**
 * @brief	Verify if the input have open quotes.
 * @param new_input string with the user input, already changed with the
 * specials characters.
 * @return 1 if it have open quotes, 0 it doesn't.
 */
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
