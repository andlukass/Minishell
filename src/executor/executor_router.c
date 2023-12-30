/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_router.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 22:23:37 by user              #+#    #+#             */
/*   Updated: 2023/12/30 22:34:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_valid_path(char *comand)
{
	char	*path;

	path = NULL;
	return (path);
}

void	executor_router(char **command)
{
	char	*path;
	char	**env;

	if (!ft_strcmp(command[0], "exit"))
		ft_exit(command);
	else if (!ft_strcmp(command[0], "pwd"))
		ft_pwd(command);
	else if (!ft_strcmp(command[0], "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command[0], "env"))
		ft_env(command);
	else if (!ft_strcmp(command[0], "export"))
		ft_export(command);
	else if (!ft_strcmp(command[0], "unset"))
		ft_unset(command);
	else if (!ft_strcmp(command[0], "cd"))
		ft_cd(command);
	path = get_valid_path(command[0]);
	if (!path)
		printf("%s: command not found :(\n", command[0]);
	else
	{
		env = env_to_array();
		execvp(command[0], command);
	}
}
//execve(path, command, env) |||| <--- AFTER get_valid_path IS DONE 
									// JUST CHANGE EXECVP BY THIS EXAMPLE
