/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:57:05 by user              #+#    #+#             */
/*   Updated: 2024/01/29 09:15:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_teste()
{
	if (get_data()->commands->command)
	{
		int i = 0;
		printf("COMMAND\n");
		while (get_data()->commands->command[i])
			printf("%s\n", get_data()->commands->command[i++]);
		printf("\n\n");
	}

	if (get_data()->commands->less_than)
		printf("LESS_THAN:\n%s\n\n\n", get_data()->commands->less_than);
	if (get_data()->commands->lt_files)
	{
		int i = 0;
		printf("LT_FILES:\n");
		while (get_data()->commands->lt_files[i])
			printf("%s\n", get_data()->commands->lt_files[i++]);
		printf("\n\n");
	}

	// if (get_data()->commands->greater_than)
	// 	printf("GREATER_THAN:\n%s\n\n\n", get_data()->commands->greater_than);
	if (get_data()->commands->gt_files)
	{
		int i = 0;
		printf("GT_FILES:\n");
		while (get_data()->commands->gt_files[i])
			printf("%s\n", get_data()->commands->gt_files[i++]);
		printf("\n\n");
	}
	if (get_data()->commands->heredocs)
	{
		int i = 0;
		printf("HEREDOCS:\n");
		while (get_data()->commands->heredocs[i])
			printf("%s\n", get_data()->commands->heredocs[i++]);
		printf("\n\n");
	}

}

void	handle_input(char *input)
{
	char	*new_input;

	add_history(input);
	new_input = lexer(input);
	if (!new_input)
		return ;
	parser(new_input);
	free(new_input);
	// print_teste();

	executor(&get_data()->commands);
	free_commands(get_data()->commands);
	get_data()->commands = NULL;
}
