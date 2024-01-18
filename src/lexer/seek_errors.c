/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:34:52 by user              #+#    #+#             */
/*   Updated: 2024/01/18 10:31:36 by user             ###   ########.fr       */
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

static int	verify_pipes(char *input)
{
	char	**splitted;
	int		index;
	int		i;
	int		result;

	index = -1;
	result = 1;
	splitted = ft_split(input, '\2');
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

int	seek_errors(char *new_input, int open_quotes)
{
	if (open_quotes)
		return (printf("there are unclosed quotes.\n"));
	if (!verify_pipes(new_input))
		return (printf("pipe syntax error.\n"));
	if (!verify_redirections(new_input))
		return (printf("redirection syntax error.\n"));
	return (0);
}
