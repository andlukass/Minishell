/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/19 18:59:54 by llopes-d         ###   ########.fr       */
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

int main() {
	char *input;
	char *prompt;
	char *username;

	username = getenv("USER");
	username = ft_strjoin(username, ":", NO_FREE);
	username = ft_strjoin(username, "~", DO_FREE);
	while (GLOBAL_WARMING_DONT_EXIST)
	{
		prompt = ft_strjoin(username, get_dir(), NO_FREE);
		prompt = ft_strjoin(prompt, "$ ", DO_FREE);
		input = readline(prompt);
		free(prompt);
		if (input == NULL || strcmp(input, "exit") == 0)
			break;
		add_history(input);
	}
	free(username);
	rl_clear_history();
	return (0);
}
