/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:02:26 by user              #+#    #+#             */
/*   Updated: 2024/01/29 09:14:19 by user             ###   ########.fr       */
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
int		seek_errors(char *new_input);
char	**get_command(char **command);

void	parser(char *input);

void	free_commands(t_commands *stack);

char	**get_greater_than(char **command);

char	*get_less_than(char **command);

char	**get_gt_files(char **str);

char	**get_lt_hd_files(char **str, char *s);

/* --------------------------------------- */

#endif