/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:03:10 by user              #+#    #+#             */
/*   Updated: 2024/01/26 11:38:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_commands	t_commands;

typedef struct s_exec		t_exec;

/* ---------------EXECUTOR---------------- */

/**
 * @brief	Execute all the commands received, handling pipes
 * and "> and >>" redirections.
 * @param commands an array of commands
 * @param fd pipe or file redirect array of fds. NULL if don't have a pipe
 */
void	executor(t_commands **commands);

/**
 * @brief	Send the execution to the right executable / builtin.
 * @param command a command formed from an array of tokens.
 */
void	executor_router(char **command, t_exec *exec);

char	*check_valid_command(char *command, t_exec *exec);

int		do_less_than(t_commands *current, t_exec *exec);

int		do_greater_than(t_commands *current, t_exec *exec);

/**
 * @brief	Close a fd[2] checking if each value is different from '-1'.
 * @param fd fd[2] with two file descriptors.
 */
void	close_fds(int *fd);

void	close_fd(int fd);

void	init_fds(int (*fd1)[2], int (*fd2)[2]);

void	exit_executor(t_exec *exec, int exit_status);

/* --------------------------------------- */

#endif