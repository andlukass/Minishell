/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:39:20 by user              #+#    #+#             */
/*   Updated: 2024/01/28 19:41:48 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	change_quotes(char *input)
{
	int		index;
	char	flag;

	index = 0;
	flag = 0;
	while (input[index])
	{
		if ((input[index] == '"' || input[index] == '\'') && !flag)
		{
			flag = input[index];
			if (input[index] == '"')
				input[index] = '\4';
			else
				input[index] = '\5';
		}
		if (input[index] == flag)
		{
			flag = 0;
			if (input[index] == '"')
				input[index] = '\4';
			else
				input[index] = '\5';
		}
		index++;
	}
}

static void	change_specials(char *input)
{
	int		index;
	char	flag;

	index = 0;
	while (input[index])
	{
		if (input[index] == '\4' || input[index] == '\5')
		{
			flag = input[index++];
			while (input[index] && input[index] != flag)
				index++;
		}
		if (input[index++] == '\0')
			break ;
		if (input[index] == ' ')
			input[index] = '\2';
		else if (input[index] == '|')
			input[index] = '\3';
		else if (input[index] == '>')
			input[index] = '\6';
		else if (input[index] == '<')
			input[index] = '\7';
	}
}

static char	*put_spaces(char *input)
{
	char	*new_input;
	int		index;
	int		j;

	j = 0;
	index = 0;
	new_input = malloc(sizeof(char) * ft_strlen(input) * 2);
	while (input[index])
	{
		new_input[j++] = input[index];
		if (input[index] == '\6' && input[index+1] && input[index + 1] == '\6')
		{
			new_input[j++] = input[index++];
			new_input[j++] = '\2';
		}
		else if (input[index] == '\7' && input[index+1] && input[index + 1] == '\7')
		{
			new_input[j++] = input[index++];
			new_input[j++] = '\2';
		}
		index++;
	}
	new_input[j] = '\0';
	return (new_input);
}

char	*lexer(char *input)
{
	char	*new_input;

	change_quotes(input);
	change_specials(input);
	new_input = put_spaces(input);
	if (seek_errors(new_input))
		return (free(new_input), NULL);
	return (new_input);
}
