/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:22:42 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/29 18:44:39 by user             ###   ########.fr       */
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

void	get_prompt_color(int argc, char *argv[])
{
	get_data()->prompt_color = NULL;
	if (argc == 1)
		return ;
	if (ft_strcmp(argv[1], "--color"))
	{
		print_error(argv[1], ": no such argument\n");
		exit(1);
	}
	if (!ft_strcmp(argv[2], "blue"))
		get_data()->prompt_color = ft_strdup(BLUE);
	else if (!ft_strcmp(argv[2], "green"))
		get_data()->prompt_color = ft_strdup(GREEN);
	else if (!ft_strcmp(argv[2], "pink"))
		get_data()->prompt_color = ft_strdup(PINK);
	else if (!ft_strcmp(argv[2], "yellow"))
		get_data()->prompt_color = ft_strdup(YELLOW);
	else if (!ft_strcmp(argv[2], "red"))
		get_data()->prompt_color = ft_strdup(RED);
	else
	{
		print_error("wrong color\ndisponible: 'blue', 'green', ", \
						"'pink', 'yellow', 'red' and 'purple'\n");
		exit(1);
	}
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*dir;

	dir = get_dir();
	prompt = ft_strjoin(get_data()->prompt_color, dir, NO_FREE);
	prompt = ft_strjoin(prompt, " \001\033[0m\002 ", DO_FREE);
	free(dir);
	return (prompt);
}
