/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:39:20 by user              #+#    #+#             */
/*   Updated: 2024/02/21 10:57:13 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Change all real quotes for \4 and \5.
 * @param input string with the user input.
 */
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

/**
 * @brief	Change all real spaces, pipes and redirections for 
 * \2, \3, \6 and \7 respectively.
 * @param input string with the user input.
 */
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
		if (input[index] == '\0')
			break ;
		if (input[index] == ' ')
			input[index] = '\2';
		else if (input[index] == '|')
			input[index] = '\3';
		else if (input[index] == '>')
			input[index] = '\6';
		else if (input[index] == '<')
			input[index] = '\7';
		index++;
	}
}

static void	change_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\5' || str[i] == '\4')
		{
			i++;
			while (str[i + 1] && str[i] != '\5' && str[i] != '\4')
				i++;
		}
		if (is_whitespace(str[i]) && str[i] != 32)
			str[i] = ' ';
		i++;
	}
}

/**
 * @brief	Put spaces('\2') after each redirect it encounters.
 * @param input string with the user input.
 * @return the new input after the spaces.
 */
static char	*put_spaces(char *input)
{
	char	*new_input;
	int		i;
	int		j;

	j = 0;
	i = -1;
	new_input = malloc(sizeof(char) * ft_strlen(input) * 3);
	while (new_input && input[++i])
	{
		new_input[j++] = input[i];
		if (input[i] != '\7' && input[i] && input[i + 1] == '\7')
			new_input[j++] = '\2';
		else if (input[i + 1] == '\7' && input[i] && input[i + 1] != '\7')
			new_input[j++] = '\2';
		else if (input[i] == '\7' && input[i] && input[i + 1] != '\7')
			new_input[j++] = '\2';
		else if (input[i] != '\6' && input[i] && input[i + 1] == '\6')
			new_input[j++] = '\2';
		else if (input[i + 1] == '\6' && input[i] && input[i + 1] != '\6')
			new_input[j++] = '\2';
		else if (input[i] == '\6' && input[i] && input[i + 1] != '\6')
			new_input[j++] = '\2';
	}
	new_input[j] = '\0';
	return (new_input);
}

char	*lexer(char *input)
{
	char	*new_input;

	change_quotes(input);
	change_whitespaces(input);
	change_specials(input);
	new_input = put_spaces(input);
	if (seek_errors(new_input))
		return (free(new_input), NULL);
	return (new_input);
}
