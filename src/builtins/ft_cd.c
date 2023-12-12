/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:14:55 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 19:38:21 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_path_valid(char **old_pwd, char *path)
{
	if (chdir(path) != 0)
	{
		perror(path);
		free(*old_pwd);
		return (0);
	}
	return (1);
}

static int	have_env(char **old_pwd)
{
	if (!get_env_value("HOME"))
	{
		printf("HOME is not set!\n");
		free(*old_pwd);
		return (0);
	}
	return (1);
}

void	ft_cd(void)
{
	char	directory[4097];
	char	*pwd;
	char	*old_pwd;

	if (get_data()->input_array[1] && get_data()->input_array[2])
	{
		printf("cd only takes one argument!\n");
		return ;
	}
	getcwd(directory, sizeof(directory));
	old_pwd = ft_strjoin("OLDPWD=", directory, NO_FREE);
	if (!get_data()->input_array[1] || !strcmp(get_data()->input_array[1], "~"))
	{
		if (!have_env(&old_pwd))
			return ;
		if (!is_path_valid(&old_pwd, get_env_value("HOME")))
			return ;
	}
	else
		if (!is_path_valid(&old_pwd, get_data()->input_array[1]))
			return ;
	getcwd(directory, sizeof(directory));
	pwd = ft_strjoin("PWD=", directory, NO_FREE);
	add_next_node(&get_data()->env, pwd);
	add_next_node(&get_data()->env, old_pwd);
}
