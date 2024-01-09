/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:59:24 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/09 17:34:35 by isbraz-d         ###   ########.fr       */
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

char	*expander(char **strs)
{
	char	*new;
	char	*sendable;
	int	i;

	i = find_string(strs);
	if (i == -1)
		return (NULL);
	sendable = get_sendable(strs[i]);
	new = malloc(sizeof(char) * ft_strlen(get_env_value(sendable)));
	if (!new)
		return (NULL);
	
}


/*
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