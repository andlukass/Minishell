/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:11:10 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/29 19:06:20 by user             ###   ########.fr       */
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
	int		i;

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

char	**edit_array(char **strs)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_cp_double_str(strs);
	free(strs);
	strs = (char **)malloc(sizeof(char *) * (count_strs(temp) + 1));
	if (!strs)
		return (NULL);
	while (temp[i])
	{
		if (ft_strcmp(temp[i], "") != 0)
			strs[j++] = temp[i++];
		else
		{
			free(temp[i]);
			i++;
		}
	}
	strs[j] = NULL;
	free(temp);
	return (strs);
}

char	**manipulate_array(char **strs, int index)
{
	char	**aux;
	char	**add;
	int		i;
	int		j;
	int		k;

	init_vars(&i, &j, &k, NULL);
	aux = ft_cp_double_str(strs);
	add = ft_split(aux[index], 32);
	free(strs);
	strs = malloc(sizeof(char *) * (count_strs(aux) + count_strs(add) + 1));
	if (!strs)
		return (NULL);
	while (i != index)
		strs[k++] = aux[i++];
	free(aux[i]);
	while (add[j])
		strs[k++] = add[j++];
	i++;
	while (aux[i])
		strs[k++] = aux[i++];
	strs[k] = NULL;
	free(aux);
	free(add);
	return (strs);
}
