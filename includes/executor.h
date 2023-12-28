/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:03:10 by user              #+#    #+#             */
/*   Updated: 2023/12/28 12:02:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_commands	t_commands;

/* ---------------EXECUTOR---------------- */

/**
 * @brief	Execute all the commands received, handling pipes
 * and "> and >>" redirections.
 * @param commands an array of commands
 * @param fd pipe or file redirect array of fds. NULL if don't have a pipe
 */
void	executor(t_commands **commands, int *fd);

/**
 * @brief	Opens all files needed by the command and put the last to
 * next_fd.
 * @param current the current command and all info of it
 * @param next_fd array of fds to be swaped by the fd of the file pointed
 * by the redirect.
 * @return the fd of the last opened file. If command donst have 
 * redirects, return -1.
 */
void	open_files(t_commands *current, int **fd, int (*next_fd)[2]);
/* --------------------------------------- */

#endif