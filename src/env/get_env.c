/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/29 13:20:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_empty_env(int index)
{
	char	directory[4097];
	char	*var;

	if (index != 0)
		return ;
	var = ft_strjoin("PWD=", getcwd(directory, sizeof(directory)), NO_FREE);
	add_next_node(&get_data()->env, ft_strdup("SHLVL=1"));
	add_next_node(&get_data()->env, ft_strdup("OLDPWD"));
	add_next_node(&get_data()->env, var);
}

void	get_env(char *env[])
{
	int		index;
	char	*variable;
	char	*level;

	index = 0;
	while (env[index])
	{
		if (!ft_strncmp(env[index], "SHLVL", 5))
		{
			level = ft_itoa(atoi(&env[index][6]) + 1);
			variable = ft_strjoin("SHLVL=", level, NO_FREE);
			free(level);
		}
		else
			variable = ft_strndup(env[index], ft_strlen(env[index]));
		add_next_node(&get_data()->env, variable);
		index++;
	}
	handle_empty_env(index);
}
