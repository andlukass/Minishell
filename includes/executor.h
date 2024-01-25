/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:03:10 by user              #+#    #+#             */
/*   Updated: 2024/01/25 15:53:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_commands	t_commands;

typedef struct s_exec	t_exec;

/* ---------------EXECUTOR---------------- */

/**
 * @brief	Execute all the commands received, handling pipes
 * and "> and >>" redirections.
 * @param commands an array of commands
 * @param fd pipe or file redirect array of fds. NULL if don't have a pipe
 */
void	executor(t_commands **commands);

/**
 * @brief	Opens all files needed by the command and put the last to
 * next_fd.
 * @param current the current command and all info of it
 * @param next_fd array of fds to be swaped by the fd of the file pointed
 * by the redirect.
 * @return the fd of the last opened file. If command donst have 
 * redirects, return -1.
 */
void	open_files(t_commands *current, t_exec *exec);

/**
 * @brief	Send the execution to the right executable / builtin.
 * @param command a command formed from an array of tokens.
 */
void	executor_router(char **command);

/**
 * @brief	Close a fd[2] checking if each value is different from '-1'.
 * @param fd fd[2] with two file descriptors.
 */
void	close_fds(int *fd);

void	exit_executor(t_exec *exec, int exit_status);
/* --------------------------------------- */

#endif