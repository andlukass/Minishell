/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:11:03 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/06 18:12:19 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_number(char **str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "<<") == 0)
			n++;
		i++;
	}
	return (n);
}

char	**get_files(char **str)
{
	char	**file;
	int	i;
	int	j;

	i = 0;
	j = 0;
	file = (char **)malloc(sizeof(char *) * get_number(str));
	if (!file)
		return (NULL);
	while (str[i])
	{
		if (ft_strcmp(str[i], "<<") == 0)
		{
			ft_strcpy(file[j], str[i + 1]);
			j++;
		}
		i++;
	}
	return (file);
}
