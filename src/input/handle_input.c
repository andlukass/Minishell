/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:57:05 by user              #+#    #+#             */
/*   Updated: 2024/01/07 14:37:09 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input(char *input)
{
	char	*new_input;

	add_history(input);
	new_input = lexer(input);
	if (!new_input)
		return ;
	parser(new_input);
	free(new_input);
	// expander(&get_data()->commands);
	// executor(&get_data()->commands);
	free_commands(get_data()->commands);
	get_data()->commands = NULL;
}
