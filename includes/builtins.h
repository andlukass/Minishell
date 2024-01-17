/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:59:28 by user              #+#    #+#             */
/*   Updated: 2024/01/17 15:28:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* ---------------BUILTINS---------------- */

/**
 * @brief	Prints the current directory.
 */
void	ft_pwd(void);

/**
 * @brief	Prints the system environment.
 * @param command a command formed from an array of tokens.
 */
void	ft_env(char **command);

/**
 * @brief	Prints the system environment or adds to it based on the
 * number of commands provided.
 * @param command a command formed from an array of tokens.
 */
void	ft_export(char **command);

/**
 * @brief	Remove from the system environment.
 * @param command a command formed from an array of tokens.
 */
void	ft_unset(char **command);

/**
 * @brief	Prints exit message, free what is needed and exit program.
 * @param command a command formed from an array of tokens.
 */
void	ft_exit(char **command, int status);

/**
 * @brief	Prints whats was the input.
 * @param command a command formed from an array of tokens.
 */
void	ft_echo(char **command);

/**
 * @brief	Change the current directory.
 * @param command a command formed from an array of tokens.
 */
void	ft_cd(char **command);

/**
 * @brief	Determines if the command is calling a builtin.
 * @param command a command formed from an array of tokens.
 * @return 1 if the command is calling a builtin, 0 if isn't.
 */
int		is_builtin(char **command);
/* --------------------------------------- */

#endif