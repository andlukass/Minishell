/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:35:38 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/24 18:20:25 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manipulate_str(char **new_str, char *add, int size)
{
	char	*temp;
	int	i;
	int	j;
	int	k;

	init_vars(&i, &j, &k, NULL);
	temp = ft_strdup(*new_str);
	// malloc protection
	free(*new_str);
	*new_str = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(add) + 1));
	if (!*new_str)
		return ;
	while (temp[k] != '$')
		(*new_str)[i++] = temp[k++];
	if ((temp[k + 1] >= '0' && temp[k + 1] <= '9') || temp[k + 1] == '?' \
		|| temp[k + 1] == '$')
		k++;
	while (add[j])
		(*new_str)[i++] = add[j++];
	k += size + 1;
	while (temp[k])
		(*new_str)[i++] = temp[k++];
	(*new_str)[i] = '\0';
	free(temp);
}
