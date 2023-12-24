/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:22:42 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/24 17:35:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_home(char *home, char *pwd)
{
	int		i;
	int		j;
	char	*dir;

	i = ft_strlen(home);
	j = 0;
	dir = malloc(sizeof(char) * ft_strlen(pwd) + 1);
	dir[j++] = '~';
	while (pwd[i])
		dir[j++] = pwd[i++];
	dir[j] = '\0';
	return (dir);
}

char	*get_dir(void)
{
	char	*pwd;
	char	*home;
	char	*dir;

	home = get_env_value("HOME");
	pwd = get_env_value("PWD");
	if (!pwd)
		return (ft_strdup("?"));
	if (!home || strncmp(home, pwd, ft_strlen(home)))
		return (ft_strdup(pwd));
	dir = replace_home(home, pwd);
	return (dir);
}

void	get_prompt(void)
{
	char	**prompt;
	char	**username;
	char	*dir;

	prompt = &get_data()->prompt;
	username = &get_data()->username;
	dir = get_dir();
	*prompt = ft_strjoin(*username, dir, NO_FREE);
	*prompt = ft_strjoin(*prompt, " ]\033[0m ", DO_FREE);
	free(dir);
}

void	get_username(void)
{
	char	**username;
	char	*env_user;

	username = &get_data()->username;
	env_user = get_env_value("USER");
	if (!env_user)
		env_user = get_env_value("HOSTNAME");
	if (!env_user)
	{
		*username = ft_strdup("user");
		return ;
	}
	*username = ft_strjoin("\033[1;96m", env_user, NO_FREE);
	*username = ft_strjoin(*username, "\033[0m in \033[1;93m[ ", DO_FREE);
}
