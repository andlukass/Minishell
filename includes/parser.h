/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:02:26 by user              #+#    #+#             */
/*   Updated: 2024/01/07 14:03:58 by isbraz-d         ###   ########.fr       */
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

void	handle_input(char *input);

char	*lexer(char *input);
int		seek_errors(char *new_input, int open_quotes);
char	**get_command(char *command);

void	parser(char *input);

void	free_commands(t_commands *stack);

char	*handle_redirections(char *command);

char	**get_files(char **str);
/* --------------------------------------- */

#endif