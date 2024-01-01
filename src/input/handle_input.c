/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:57:05 by user              #+#    #+#             */
/*   Updated: 2024/01/01 13:58:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input(char *input)
{
	char	*new_input;
	
	// new_input = lexer(input);
	// parser(new_input);
	executor(&get_data()->commands);
	free_commands(get_data()->commands);
	get_data()->commands = NULL;
	add_history(input);
}
