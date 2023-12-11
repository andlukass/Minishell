/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:22:42 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 23:37:13 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_home(char *copy)
{
	int	copy_index;
	int	home_index;
	char	*home;
	char	*pwd;


	copy_index = 0;
	home_index = 0;
	pwd = get_env_value("PWD");
	home = get_env_value("HOME");
	copy[copy_index++] = '~';
	if (!strcmp(home, pwd))
		return ;
	copy[copy_index++] = '/';
	while (pwd[home_index] == home[home_index])
		home_index++;
	while (pwd[home_index])
	{
		copy[copy_index] = pwd[home_index];
		copy_index++;
		home_index++;
	}
	copy[copy_index] = '\0';

	//enquanto pwd for igual ao home aumenta o index de copy, quando for diferente, adiciona ~/ nos 
	//indices 0 e 1, e entao começa a copiar 
}

char	*get_dir(void)
{
	char	*home;
	char	*pwd;
	char	*occurrence;
	char	*copy;

	home = get_env_value("HOME");
	pwd = get_env_value("PWD");
	if (!strncmp(home, pwd, ft_strlen(home)))
	{
		replace_home(copy);
		occurrence = strdup(copy);
	}
	else
		occurrence = strdup(pwd);
	return (occurrence);
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
	*prompt = ft_strjoin(*prompt, "]\033[0m ", DO_FREE);
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
		*username = strdup("user");
		return ;
	}
	*username = ft_strjoin(" \033[1;96m", *username, NO_FREE);
	*username = ft_strjoin(*username, env_user, DO_FREE);
	*username = ft_strjoin(*username, "\033[0m", DO_FREE);
	*username = ft_strjoin(*username, " ", DO_FREE);
	*username = ft_strjoin(*username, "in ", DO_FREE);
	*username = ft_strjoin(*username, "\033[1;93m[", DO_FREE);
}
