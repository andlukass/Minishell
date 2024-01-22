/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:59:24 by isbraz-d          #+#    #+#             */
/*   Updated: 2024/01/22 11:52:14 by isbraz-d         ###   ########.fr       */
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

void	expander_heredoc(char **str)
{
	char	*add;
	char	*sendable;

	while (there_is_expansion(*str))
	{
		sendable = get_sendable(*str);
		add = ft_strdup(get_env_value(sendable));
		if (add == NULL)
		{
			if (search_special_expansions(*str) == 1)
				add = ft_strdup("minishell");
			else if (search_special_expansions(*str) == 2)
				add = ft_itoa(get_data()->exit_status / 256);
			else if (search_special_expansions(*str) == 3)
				add = ft_itoa(get_data()->pid);
			else
				add = ft_strdup("");
		}
		manipulate_str(str, add, ft_strlen(sendable));
		free(add);
		free(sendable);
	}
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
	 
*/