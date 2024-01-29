/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:03:10 by user              #+#    #+#             */
/*   Updated: 2024/01/29 15:32:20 by user             ###   ########.fr       */
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

/**
 * @brief	Checks if the command is valid.
 * @param command first string of the command.
 * @param exec structure with all the variables used by the executer.
 * @return if its a valid command, returns the path, if not, NULL instead.
 */
char	*check_valid_command(char *command, t_exec *exec);

/**
 * @brief	Opens all the "<" redirections, including heredocs.
 * @param current structure with all the command data.
 * @param exec structure with all the variables used by the executer.
 * @return the opened file descriptor, -1 if none was open, -2 if invalid 
 * file.
 */
int		do_less_than(t_commands *current, t_exec *exec);

/**
 * @brief	Opens all the ">" redirections.
 * @param current structure with all the command data.
 * @param exec structure with all the variables used by the executer.
 * @return the opened file descriptor, -1 if none was open, -2 if invalid 
 * file.
 */
int		do_greater_than(t_commands *current, t_exec *exec);

/**
 * @brief	Clean all exec variables. If its a valid exit_status
 * terminate the process cleaning all program use.
 * @param exec structure with all the variables used by the executer.
 * @param exit_status what to send to exit() function.
 */
void	exit_executor(t_exec *exec, int exit_status);

/**
 * @brief	Close a fd[2] checking if each value is different from '-1'.
 * @param fd fd[2] with two file descriptors.
 */
void	close_fds(int *fd);

/**
 * @brief	Close a fd checking if its value is different from '-1'.
 * @param fd file descriptors.
 */
void	close_fd(int fd);

/**
 * @brief	Set the values of a fd[2] to -1.
 * @param fd1 file descriptors(can be NULL).
 * @param fd2 file descriptors(can be NULL).
 */
void	init_fds(int (*fd1)[2], int (*fd2)[2]);

/* --------------------------------------- */

#endif