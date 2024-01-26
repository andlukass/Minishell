/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:33:16 by user              #+#    #+#             */
/*   Updated: 2024/01/26 12:39:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char const *s1, unsigned int n)
{
	char			*duplicate;
	unsigned int	index;

	index = 0;
	if (!s1 || n == 0)
		return (NULL);
	duplicate = malloc(sizeof(char) * (n + 1));
	if (duplicate == NULL)
		return (NULL);
	while (s1[index] && index < n)
	{
		duplicate[index] = s1[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}
