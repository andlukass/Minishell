/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:07:23 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/18 17:21:00 by isbraz-d         ###   ########.fr       */
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
			j++;
		if (temp[j] == '\6')
			temp[j] = '$'; 
		(*str)[i++] = temp[j++];
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


/*	
	remove: \4, \5;
	replace : \6 = $;
*/