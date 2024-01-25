/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_router.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:23:37 by user              #+#    #+#             */
/*   Updated: 2024/01/25 17:36:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_directory(char *path, char *command)
{
	char			*valid_path;
	struct dirent	*entity;
	DIR				*dir;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	entity = readdir(dir);
	valid_path = NULL;
	while (entity != NULL)
	{
		if (!ft_strcmp(entity->d_name, command))
		{
			valid_path = ft_strjoin(path, "/", NO_FREE);
			valid_path = ft_strjoin(valid_path, command, DO_FREE);
			break ;
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (valid_path);
}

static char	*search_on_env_path(char *command)
{
	char			*valid_path;
	char			**directories;
	int				index;

	directories = ft_split(get_env_value("PATH"), ':');
	index = 0;
	valid_path = NULL;
	while (directories[index])
	{
		valid_path = check_directory(directories[index], command);
		if (valid_path)
			break ;
		index++;
	}
	free_double_array(directories);
	return (valid_path);
}

static int	do_bultins(char **commands)
{
	int	is_builtin;

	is_builtin = 1;
	if (!ft_strcmp(commands[0], "exit"))
		ft_exit(commands, 0);
	else if (!ft_strcmp(commands[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(commands[0], "echo"))
		ft_echo(commands);
	else if (!ft_strcmp(commands[0], "env"))
		ft_env(commands);
	else if (!ft_strcmp(commands[0], "export"))
		ft_export(commands);
	else if (!ft_strcmp(commands[0], "unset"))
		ft_unset(commands);
	else if (!ft_strcmp(commands[0], "cd"))
		ft_cd(commands);
	else
		is_builtin = 0;
	return (is_builtin);
}

char	*check_valid_command(char *command, t_exec *exec)
{
	char		*valid_path;
	struct stat	info;

	valid_path = NULL;
	if (command[0] == '/' || (command[0] == '.' && \
		(command[1] == '/' || command[1] == '.')))
	{
		if (stat(command, &info) == 0)
			valid_path = command;
	}
	else
		valid_path = search_on_env_path(command);
	if (!valid_path)
	{
		printf("%s: not found :(\n", command);
		exit_executor(exec, 127);
	}
	return (valid_path);
}

void	executor_router(char **command, t_exec *exec)
{
	char	*valid_path;
	char	**env;

	if (!command)
		ft_exit(NULL, 0);
	if (do_bultins(command))
		return ;
	valid_path = check_valid_command(command[0], exec);
	env = env_to_array();
	if (execve(valid_path, command, env))
	{
		perror(valid_path);
		free_double_array(env);
		ft_exit(NULL, 126);
	}
}

/*
	sem permissão: 126
	nao existe: 127
*/