/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:11:10 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/25 14:39:42 by isbraz-d         ###   ########.fr       */
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
		i++;
	}
	cp[i] = NULL; 
	return (cp);
}

char	**manipulate_array(char **strs, int index)
{
	char	**aux;
	char	**add;
	int	i;
	int	j;
	int	k;

	init_vars(&i, &j, &k, NULL);
	aux = ft_cp_double_str(strs);
	add = ft_split(aux[index], 32);
	free(strs);
	strs = (char **)malloc(sizeof(char *) * (count_strs(aux) + count_strs(add) + 1));
	if (!strs)
		return (NULL);
	while (i != index)
	{
		strs[k++] = aux[i++];
		// aux[i++] = NULL;
	}
	free(aux[i]);
	while (add[j])
	{
		strs[k++] = add[j++];
		// add[j++] = NULL;
	}
	i++;
	while (aux[i])
	{
		strs[k++] = aux[i++];
		// aux[i] = NULL;
	}
	strs[k] = NULL;
	free(aux);
	free(add);
	return(strs);
}
