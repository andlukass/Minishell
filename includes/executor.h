/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:03:10 by user              #+#    #+#             */
/*   Updated: 2023/12/25 12:50:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/* ---------------EXECUTOR---------------- */

/**
 * @brief	Execute all the commands received, handling pipes
 * and "> and >>" redirections.
 * @param commands an array of commands
 * @param fd pipe generated array of fds. NULL if don't have a pipe
 */
void	executor(t_commands **commands, int *fd);

/**
 * @brief	Opens all files needed by the command and put the last to
 * next_fd.
 * @param current the current command and all info of it
 * @param next_fd array of fds.
 */
int		open_files(t_commands *current, int (*next_fd)[2]);
/* --------------------------------------- */

#endif