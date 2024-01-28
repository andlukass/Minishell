/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:07:23 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/28 19:34:00 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	edit_str(char **str)
{
	char	*temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	temp = ft_strdup(*str);
	free(*str);
	*str = malloc(sizeof(char) * ft_strlen(temp) + 1);
	while (temp[j])
	{
		if (temp[j] == '\4' || temp[j] == '\5')
		{
			j++;
			continue;
		}
		else if (temp[j] == '\1')
			temp[j] = '$';
		if (temp[j] != '\4' && temp[j] != '\5')
			(*str)[i++] = temp[j];
		j++;
	}
	(*str)[i] = '\0';
	free(temp);
}

char	**rm_quotes(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		edit_str(&strs[i]);
		i++;
	}
	return (strs);
}
