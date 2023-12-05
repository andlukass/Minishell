/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:22:42 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/05 20:28:00 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_dir(void)
{
	char	*home;
	char	*home_dir_name;
	char	*pwd;
	char	*occurrence;

	home = get_env_value("HOME");
	home_dir_name = ft_strrchr(home, '/') + 1;
	pwd = get_env_value("PWD");
	occurrence = strstr(pwd, home_dir_name);
	occurrence = occurrence + strlen(home_dir_name);
	return (occurrence);
}

void	get_prompt(void)
{
	char	**prompt;
	char	**username;

	prompt = &get_data()->prompt;
	username = &get_data()->username;
	*prompt = ft_strjoin(*username, get_dir(), NO_FREE);
	// *prompt = ft_strjoin(*prompt, "] ", DO_FREE);
	*prompt = ft_strjoin(*prompt, "]\033[0m ", DO_FREE);
}

void	get_username(void)
{
	char	**username;
	char	*env_user;

	username = &get_data()->username;
	env_user = get_env_value("USER");
	*username = ft_strjoin(" \033[1;96m", *username, NO_FREE);
	*username = ft_strjoin(*username, env_user, DO_FREE);
	*username = ft_strjoin(*username, "\033[0m", DO_FREE);
	// *username = ft_strjoin(*username, " ", DO_FREE);
	*username = ft_strjoin(*username, "in ", DO_FREE);
	// *username = ft_strjoin(*username, "[~", DO_FREE);
	*username = ft_strjoin(*username, "\033[1;93m[~", DO_FREE);
}
