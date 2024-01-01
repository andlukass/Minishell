/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:47:57 by user              #+#    #+#             */
/*   Updated: 2024/01/01 13:33:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	do_multable_builtin(t_commands *current)
{
	if (!current->next && \
		(!ft_strcmp(current->command[0], "exit") || \
		!ft_strcmp(current->command[0], "export") || \
		!ft_strcmp(current->command[0], "unset") || \
		!ft_strcmp(current->command[0], "cd")))
	{
		executor_router(current->command);
		return (1);
	}
	else
		return (0);
}

static void	child_routine(t_commands *cur, int *next_fd, int *fd, int **pids)
{
	if (next_fd[1] != -1)
		dup2(next_fd[1], STDOUT_FILENO);
	if (fd[0] != -1)
		dup2(fd[0], STDIN_FILENO);
	if (next_fd[0] != -1 && cur->less_than)
		dup2(next_fd[0], STDIN_FILENO);
	close_fds(fd);
	close_fds(next_fd);
	free(*pids);
	executor_router(cur->command);
}
/*
IFS:
	1º cancelar o proprio stdout ex: echo teste | cat ou echo teste > teste.txt
	2º cancelar o proprio stdin | ex: echo teste | cat
	3º cancelar o proprio stdin | ex: cat < teste.txt
*/

static void	do_commands(t_commands *current, int **pids, int (*fd)[2])
{
	int	next_fd[2];
	int	index;

	index = 0;
	while (current)
	{
		next_fd[0] = -1;
		next_fd[1] = -1;
		if (current->next)
			if (pipe(next_fd) < 0)
				exit(0);
		open_files(current, &next_fd);
		(*pids)[index] = fork();
		if ((*pids)[index] < 0)
			exit(0);
		if ((*pids)[index++] == 0)
			child_routine(current, next_fd, *fd, pids);
		close_fds(*fd);
		(*fd)[0] = next_fd[0];
		(*fd)[1] = next_fd[1];
		current = current->next;
	}
	close_fds(next_fd);
}

void	executor(t_commands **commands)
{
	t_commands	*current;
	int			fd[2];
	int			index;
	int			*pids;
	int			number_of_pids;

	number_of_pids = get_data()->number_of_commands;
	current = *commands;
	if (do_multable_builtin(current))
		return ;
	pids = malloc(sizeof(int) * number_of_pids);
	fd[0] = -1;
	fd[1] = -1;
	do_commands(current, &pids, &fd);
	index = 0;
	while (index < number_of_pids)
		waitpid(pids[index++], &get_data()->exit_status, 0);
	free(pids);
}
