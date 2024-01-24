/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:11:10 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/24 19:16:02 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_strs(char **strs)
{
	int	i;
	
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

static char	**ft_cp_double_str(char **strs)
{
	char	**cp;
	int	i;

	cp = (char **)malloc(sizeof(char *) * (count_strs(strs) + 1));
	if (!cp)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		cp[i] = strs[i];
		strs[i] = NULL;
		//malloc prtocetion e free
		i++;
	}
	cp[i] = NULL; 
	return (cp);
}

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

char	**manipulate_array(char **strs, int index)
{
	char	**aux;
	char	**add;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	aux = ft_cp_double_str(strs);
	add = ft_split(aux[index], 32);
	free(strs);
	strs = (char **)malloc(sizeof(char *) * (count_strs(aux) + count_strs(add) + 1));
	if (!strs)
		return (NULL);
	while (i != index)
	{
		strs[k++] = aux[i];
		aux[i] = NULL;
		i++;
	}
	while (add[j])
	{
		strs[k++] = add[j];
		add[j] = NULL;
		j++;
	}
	i++;
	while (aux[i])
	{
		strs[k++] = aux[i];
		aux[i] = NULL;
		i++;
	}
	strs[k] = NULL;
	free(aux);
	free(add);
	return(strs);
}
