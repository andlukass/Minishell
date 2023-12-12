/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:04 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/26 13:11:09 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2, int is_free)
{
	char	*newstr;
	int		index;
	int		length;

	if (!s1 && is_free)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	newstr = (char *) malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1)
			* sizeof(char));
	if (newstr == (void *)0)
		return ((void *)0);
	index = 0;
	length = -1;
	while (s1[++length])
		newstr[length] = s1[length];
	while (s2 && s2[index])
		newstr[length++] = s2[index++];
	if (is_free)
		free(s1);
	newstr[length] = '\0';
	return (newstr);
}
