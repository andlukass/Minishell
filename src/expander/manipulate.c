/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:35:38 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/02/20 12:34:05 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_array(char **array)
// {
// 	printf("[");
// 	while (array && *array)
// 	{
// 		if (!*(array + 1))
// 			printf("%s", *array++);
// 		else
// 			printf("%s, ", *array++);
// 	}
// 	printf("]\n");
// }

void	manipulate_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\10')
			str[i] = '$';
		i++;
	}
}

char	*manipulate_str(char **new_str, char *add, int size)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	init_vars(&i, &j, &k, NULL);
	temp = *new_str;
	*new_str = NULL;
	free(*new_str);
	*new_str = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(add) + 1));
	if (!*new_str)
		return (NULL);
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
	return (*new_str);
}
