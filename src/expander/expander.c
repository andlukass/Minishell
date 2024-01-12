/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:59:24 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/12 16:57:45 by isbraz-d         ###   ########.fr       */
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
			if (strs[i][j] == '$' && strs[i][j + 1] != '\0')
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
		sendable[j++] = str[i++];
	sendable[j] = '\0';
	return (sendable);
}

static int	search_expand_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '0')
			return (1);
		i++;
	}
	return (0);
}

static void	change_str(char **new, char *add, int size)
{
	char	*temp;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	temp = ft_strdup(*new);
	free(*new);
	*new = malloc(sizeof(char) * (ft_strlen(temp) + ft_strlen(add) + 1));
	if (!*new)
		return ;
	while (temp[k] != '$')
		(*new)[i++] = temp[k++];
	if (temp[k + 1] >= '0' && temp[k + 1] <= '9')
		k++;
	while (add[j])
		(*new)[i++] = add[j++];
	k += size + 1;
	while (temp[k])
		(*new)[i++] = temp[k++];
	(*new)[i] = '\0';
	free(temp);
}

char **expander(char **strs)
{
    int i;
    char *add;
    char *sendable;

	i = 0;
	while ((i = find_string(strs)) != -1)
	{
		sendable = get_sendable(strs[i]);
		add = ft_strdup(get_env_value(sendable));
		if (add == NULL)
		{
			if (search_expand_zero(strs[i]))
				add = ft_strdup("minishell");
			else
				add = ft_strdup("");
		}
		change_str(&strs[i], add, ft_strlen(sendable));
		free(sendable);
		free(add);
	}
	return (strs);
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