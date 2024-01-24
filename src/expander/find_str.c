/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:46:01 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/24 15:20:50 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_quoted_expansion(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\5' && str[i])
		{
			i++;
			while (str[i] && str[i] != '\5')
			{
				if (str[i] == '$')
					str[i] = '\6';
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	there_is_expansion(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

int	find_string(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '$' && strs[i][j + 1] != '\0')
				handle_quoted_expansion(strs[i]);
			if (strs[i][j] == '$' && strs[i][j + 1] != '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
