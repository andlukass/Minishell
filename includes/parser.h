/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 17:02:26 by user              #+#    #+#             */
/*   Updated: 2024/01/01 12:42:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_commands	t_commands;

/* ----------------PARSER----------------- */

void	handle_input(char *input);
void	free_commands(t_commands *stack);
/* --------------------------------------- */

#endif