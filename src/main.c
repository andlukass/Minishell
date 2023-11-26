/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/26 14:02:28 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_dir()
{
	char *home;
	char *home_dir_name;
	char *pwd;
	char *occurrence;

	home = getenv("HOME");
	home_dir_name = ft_strrchr(home, '/') + 1;
	pwd = getenv("PWD");
	occurrence = strstr(pwd, home_dir_name);
	occurrence = occurrence + strlen(home_dir_name);
	return occurrence;
}

void	get_prompt()
{
	char **prompt;
	char **username;

	prompt = &get_data()->prompt;
	username = &get_data()->username;
	*prompt = ft_strjoin(*username, get_dir(), NO_FREE);
	*prompt = ft_strjoin(*prompt, "]\033[0m ", DO_FREE);
}

void	get_username(void)
{
	char **username;
	char *env_user;

	username = &get_data()->username;
	env_user = getenv("USER");
	*username = NULL;
	*username = ft_strjoin(" \033[1;96m", *username, NO_FREE);
	*username = ft_strjoin(*username, env_user, DO_FREE);
	*username = ft_strjoin(*username, "\033[0m", DO_FREE);
	*username = ft_strjoin(*username, " ", DO_FREE);
	*username = ft_strjoin(*username, "in ", DO_FREE);
	*username = ft_strjoin(*username, "\033[1;93m[~", DO_FREE);
}

int main(int argc, char *argv[], char *env[]) {
	t_data *data;

	(void)argv;
	(void)env;

	if (argc != 1)
		return (write(1, "too many arguments", 1));
	data = get_data();
	get_username();
	while (GLOBAL_WARMING_DONT_EXIST)
	{
		get_prompt();
		data->input = readline(data->prompt);
		free(data->prompt);
		if (data->input == NULL || strcmp(data->input, "exit") == 0)
			break;
		add_history(data->input);
	}
	free(data->username);
	rl_clear_history();
	return (0);
}
