/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:59:24 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/21 23:22:22 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	search_special_expansions(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '0')
			return (1);
		if (str[i] == '$' && str[i + 1] == '?')
			return (2);
		if (str[i] == '$' && str[i + 1] == '$')
			return (3);
		i++;
	}
	return (0);
}

int	get_process(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(0);
	return (pid - 1);
}

void	expander_heredoc(char **str, char *sendable)
{
	char	*add;

	add = ft_strdup(get_env_value(sendable));
	manipulate_str(str, add, ft_strlen(sendable));
	free(add);
	free(sendable);
}

char **expander(char **strs)
{
    int i;
    char *add;
    char *sendable;

	i = 0;
	while ((i = find_string(strs)) != -1)
	{
		if (i != 0 && ft_strcmp(strs[i - 1], "<<") == 0)
			break;
		sendable = get_sendable(strs[i]);
		add = ft_strdup(get_env_value(sendable));
		if (add == NULL)
		{
			if (search_special_expansions(strs[i]) == 1)
				add = ft_strdup("minishell");
			else if (search_special_expansions(strs[i]) == 2)
				add = ft_itoa(get_data()->exit_status / 256);
			else if (search_special_expansions(strs[i]) == 3)
				add = ft_itoa(get_data()->pid);
			else
				add = ft_strdup("");
		}
		manipulate_str(&strs[i], add, ft_strlen(sendable));
		free(sendable);
		free(add);
	}
	return (rm_quotes(strs), strs);
}

/*

STR[I] == \5
	echo \5$PWD\5$home

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