/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:59:24 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/11 20:06:34 by isbraz-d         ###   ########.fr       */
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
			add = ft_strdup("");
        change_str(&strs[i], add, ft_strlen(sendable));
        free(sendable);
        free(add);
    }
    return (strs);
}

// char	*expander(char **strs)
// {
// 	char	*add;
// 	char	*sendable;
// 	int	i;

// 	add = ft_strdup(get_env_value(sendable));
// 	i = find_string(strs);
// 	sendable = get_sendable(strs[i]);
// 	if (i == -1)
// 		return (NULL);
// 	change_str(&strs[i], add, ft_strlen(sendable));
// 	free(sendable);
// 	return (NULL);
// }


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