/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:02:26 by user              #+#    #+#             */
/*   Updated: 2024/01/29 16:26:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_commands	t_commands;

/* ----------------PARSER----------------- */
/**
 * @brief	Concatenates the username with the current directory
 * and end the terminal stylization.
 * The prompt is stored in the global data.
 */
char	*get_prompt(void);

/**
 * @brief	Handle the user input and route it to the executer.
 * @param input the user input.
 */
void	handle_input(char *input);

/**
 * @brief	Prepare the input for the parser function and check errors.
 * @param input the user input.
 * @return the new changed string.
 */
char	*lexer(char *input);

/**
 * @brief	Check pipe, redirects and quote errors.
 * @param new_input the user input already with the special charachters.
 * @return 1 if the input have erros, 0 if doesn't.
 */
int		seek_errors(char *new_input);

/**
 * @brief	Get all the user command into a array of strings, removing
 * all redirect, and file names.
 * @param command the user command splitted in spaces('\2').
 */
char	**get_command(char **command);

/**
 * @brief	Split the user input into pipes('\3'). And build the struct
 * with all redirect, files and commands.
 * @param input the user input already with the special charachters.
 */
void	parser(char *input);

/**
 * @brief	Pass through all the struct nodes, and free all.
 * @param stack the node in which to begin.
 */
void	free_commands(t_commands *stack);

/**
 * @brief	Checks if the command have greater_than redirects
 * @param command the user command splitted in spaces('\2').
 * @return array with all the append or truncates.
 */
char	**get_greater_than(char **command);

/**
 * @brief	Gets the last less_than redirection.
 * @param command the user command splitted in spaces('\2').
 * @return "<", "<<" or NULL if the command dont have 
 * less_than redirects.
 */
char	*get_less_than(char **command);

/**
 * @brief	Checks if the command have greater_than redirects.
 * @param str the user command splitted in spaces('\2').
 * @return array with all the file names to open.
 */
char	**get_gt_files(char **str);

/**
 * @brief	Checks if the command have less_than redirects or heredocs.
 * @param str the user command splitted in spaces('\2').
 * @param s string to determine if it is a heredoc or a redirection, "\7\7",
 * "\7" respectively.
 * @return array with all the file names to open / heredoc to listen.
 */
char	**get_lt_hd_files(char **str, char *s);

/* --------------------------------------- */

#endif