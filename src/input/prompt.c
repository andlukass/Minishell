/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:22:42 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/29 16:18:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_home(char *home, char *pwd)
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

static char	*get_dir(void)
{
	char	*pwd;
	char	*home;
	char	*dir;

	home = get_env_value("HOME");
	pwd = get_env_value("PWD");
	if (!pwd)
		return (ft_strdup("?"));
	if (!home || ft_strncmp(home, pwd, ft_strlen(home)))
		return (ft_strdup(pwd));
	dir = replace_home(home, pwd);
	return (dir);
}

static char	*get_username(void)
{
	char	*username;
	char	*env_user;

	env_user = get_env_value("USER");
	if (!env_user)
		env_user = get_env_value("HOSTNAME");
	if (!env_user)
		username = ft_strdup("\033[1;96muser");
	else
		username = ft_strjoin("\033[1;96m", env_user, NO_FREE);
	username = ft_strjoin(username, "\033[0m in \033[1;93m[ ", DO_FREE);
	return (username);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*username;
	char	*dir;

	username = get_username();
	dir = get_dir();
	prompt = ft_strjoin(username, dir, DO_FREE);
	prompt = ft_strjoin(prompt, " ]\033[0m ", DO_FREE);
	free(dir);
	return (prompt);
}
