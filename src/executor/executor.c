/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:47:57 by user              #+#    #+#             */
/*   Updated: 2024/01/25 17:38:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	do_multable_builtin(t_commands *current, t_exec *exec)
{
	if (!current->command)
		return (0);
	if (!current->next && \
		(!ft_strcmp(current->command[0], "exit") || \
		!ft_strcmp(current->command[0], "export") || \
		!ft_strcmp(current->command[0], "unset") || \
		!ft_strcmp(current->command[0], "cd")))
	{
		exec->files[0] = do_less_than(current, exec);
		exec->files[1] = do_greater_than(current);
		executor_router(current->command, exec);
		return (1);
	}
	else
		return (0);
}

static void	child_routine(t_commands *current, t_exec *exec)
{
	char	*valid_path;

	if (exec->files[0] == -2)
		exit_executor(exec, 1);
	if (current->command)
	{
		valid_path = check_valid_command(current->command[0], exec);
		if (!valid_path)
			exit_executor(exec, 127);
		free(valid_path);
	}
	if (exec->next_fd[1] != -1)
		dup2(exec->next_fd[1], STDOUT_FILENO);
	if (exec->fd[0] != -1)
		dup2(exec->fd[0], STDIN_FILENO);
	if (exec->files[0] != -1)
		dup2(exec->files[0], STDIN_FILENO);
	if (exec->files[1] != -1)
		dup2(exec->files[1], STDOUT_FILENO);
	exit_executor(exec, -1);
	executor_router(current->command, exec);
}

static int	do_commands(t_commands *current, t_exec *exec)
{
	int	index;

	index = 0;
	while (current)
	{
		init_fds(&exec->next_fd, &exec->files);
		if (current->next)
			if (pipe(exec->next_fd) < 0)
				exit_executor(exec, 1);
		exec->files[0] = do_less_than(current, exec);
		exec->files[1] = do_greater_than(current);
		if (get_data()->quit)
			return (exit_executor(exec, -1), 0);
		exec->pids[index] = fork();
		if (exec->pids[index] < 0)
			exit_executor(exec, 1);
		if (exec->pids[index++] == 0)
			child_routine(current, exec);
		close_fds(exec->fd);
		close_fds(exec->files);
		exec->fd[0] = exec->next_fd[0];
		exec->fd[1] = exec->next_fd[1];
		current = current->next;
	}
	return (close_fds(exec->next_fd), 1);
}

void	executor(t_commands **commands)
{
	t_commands	*current;
	t_exec		exec;
	int			index;
	int			number_of_pids;

	number_of_pids = get_data()->number_of_commands;
	current = *commands;
	if (do_multable_builtin(current, &exec))
		return ;
	exec.pids = malloc(sizeof(int) * number_of_pids);
	init_fds(&exec.fd, NULL);
	if (!do_commands(current, &exec))
		return ;
	index = 0;
	while (index < number_of_pids)
		waitpid(exec.pids[index++], &get_data()->exit_status, 0);
	free(exec.pids);
}
