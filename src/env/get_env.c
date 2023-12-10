/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 22:23:38 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_env(char *env[])
{
	int		index;
	char	*variable;
	char	*level;

	index = 0;
	while (env[index])
	{
		if (!strncmp(env[index], "SHLVL", 5))
		{
			level = ft_itoa(atoi(&env[index][6]) + 1);
			variable = ft_strjoin("SHLVL=", level, NO_FREE);
			free(level);
		}
		else
			variable = strndup(env[index], ft_strlen(env[index]));
		add_next_node(&get_data()->env, create_new_value(variable));
		index++;
	}
}
