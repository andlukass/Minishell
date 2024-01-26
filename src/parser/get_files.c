/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:04:26 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/26 12:43:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_lt_hd_files(char **str, char *s)
{
	char	**file;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	file = (char **)malloc(sizeof(char *) * i);
	i = 0;
	if (!file)
		return (NULL);
	while (str[i])
	{
		if (ft_strcmp(str[i], s) == 0)
		{
			file[j] = ft_strdup(str[i + 1]);
			j++;
		}
		i++;
	}
	file[j] = NULL;
	if (j == 0)
		return (free_double_array(file), NULL);
	return (file);
}

char	**get_gt_files(char **str)
{
	char	**file;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	file = (char **)malloc(sizeof(char *) * i);
	i = 0;
	if (!file)
		return (NULL);
	while (str[i])
	{
		if (ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], ">>") == 0)
		{
			file[j] = ft_strdup(str[i + 1]);
			j++;
		}
		i++;
	}
	file[j] = NULL;
	if (j == 0)
		return (free_double_array(file), NULL);
	return (file);
}
