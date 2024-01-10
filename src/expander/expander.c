/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:59:24 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/10 20:58:50 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_string(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '$')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

static char	*get_sendable(char *str)
{
	char	*sendable;
	int	i;
	int	j;

	i = 0;
	j = 0;
	sendable = malloc(sizeof(char) * ft_strlen(str));
	if (!sendable)
		return (NULL);
	while (str[i] != '$') 
		i++;
	i++;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
	{
		sendable[j] = str[i];
		j++;
		i++;
	}
	sendable[j] = '\0';
	return (sendable);
}
static void	change_str(char **old, char *new)
{
	char	*temp;
	int	i;
	int	j;
	int	k;
	
	i = 0;
	j = 0;
	k = 0;
	temp = ft_strdup(*old);
	free(*old);
	*old = malloc(ft_strlen(temp) + ft_strlen(new));
	if (!*old)
		return (NULL);
	while (temp[k] != '$')
	{
		*old[i] = temp[k];
		i++;
		k++;
	}
	while (new)
	{
		*old[i] = new[j];
		i++;
		j++;
	}
	while (temp[k])
	{
		*old[i] = temp[k];
		i++;
		k++;
	}
	*old[i] = '\0';
}

char	*expander(char **strs)
{
	char	*new;
	char	*sendable;
	int	i;

	i = find_string(strs);
	if (i == -1)
		return (NULL);
	sendable = get_sendable(strs[i]);
	new = ft_strdup(get_env_value(sendable));
	change_str(strs[i], new);
	free(sendable);
	
}


/*
	$PWD
	
	coisas que são aceitas na string com a expansão:
	letrasantes$PWD
	$PWD. (pode haver coisas dps do .)
	$PWD, (pode haver coisas dps da ,)
	$PWD- (pode haver coisas dps da -)
	coisas não aceitas na expansão:
	$PWD_
	$PWDletrasdepois
	
	aspas :
	echo "$PW"D ----> se o que estiver nas aspas nao estiver no env,
	ignora e printa o que estiver dps caso contrario:
	echo "$PWD"D
	 
*/