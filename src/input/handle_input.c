/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:57:05 by user              #+#    #+#             */
/*   Updated: 2024/01/05 15:00:46 by user             ###   ########.fr       */
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
	// parser(new_input);
	char **teste = ft_split(new_input, '\2');
	int i = 0;
	while (teste[i])
		printf("%s\n", teste[i++]);
		
	free(new_input);
	// expander(&get_data()->commands);
	// executor(&get_data()->commands);
	// free_commands(get_data()->commands);
	get_data()->commands = NULL;
}
