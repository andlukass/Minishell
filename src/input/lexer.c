/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:39:20 by user              #+#    #+#             */
/*   Updated: 2024/01/01 21:11:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (free_double_array(splitted) ,result);
}

static int	seek_errors(char *new_input, int open_quotes)
{
	if (open_quotes)
		return (printf("there are unclosed quotes.\n"));
	if (!verify_pipes(new_input))
		return (printf("pipe syntax error.\n"));
	if (ft_strchr(new_input, ';'))
		return (printf("not interpreted character: ';'.\n"));
	return (0);
}

static void	check_quotes(char c, int *double_q, int *single_q)
{
	if (c == '\"' && *double_q == 0 && *single_q == 0)
		*double_q = 1;
	else if (c == '\"' && *double_q == 1 && *single_q == 0)
		*double_q = 0;
	if (c == '\'' && *single_q == 0 && *double_q == 0)
		*single_q = 1;
	else if (c == '\'' && *single_q == 1 && *double_q == 0)
		*single_q = 0;
}

char	*lexer(char *input)
{
	char	*new_input;
	int		index;
	int		double_q;
	int		single_q;

	index = 0;
	double_q = 0;
	single_q = 0;
	new_input = malloc(sizeof(char) * ft_strlen(input) + 1);
	while (input[index])
	{
		if (input[index] == ' ' && (double_q == 0 && single_q == 0))
			new_input[index] = '\2';
		else if (input[index] == '|' && (double_q == 0 && single_q == 0))
			new_input[index] = '\3';
		else
			new_input[index] = input[index];
		check_quotes(input[index], &double_q, &single_q);
		index++;
	}
	new_input[index] = '\0';
	if (seek_errors(new_input, single_q + double_q))
		return (free(new_input), NULL);
	return (new_input);
}
