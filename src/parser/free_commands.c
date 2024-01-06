/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:32 by user              #+#    #+#             */
/*   Updated: 2024/01/06 11:11:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_commands(t_commands *stack)
{
	t_commands	*current;
	t_commands	*temp;

	current = stack;
	while (current->next)
	{
		temp = current->next;
		free_double_array(current->command);
		if (current->greater_than) {
			free_double_array(current->gt_files);
			free(current->greater_than);
		}
		if (current->less_than) {
			free_double_array(current->lt_files);
			free(current->less_than);
		}
		if (current->heredocs)
			free_double_array(current->heredocs);
		free(current);
		current = temp;
	}
	free_double_array(current->command);
	if (current->greater_than) {
		free_double_array(current->gt_files);
		free(current->greater_than);
	}
	if (current->lt_files)
		free_double_array(current->lt_files);
	if (current->less_than)
		free(current->less_than);
	if (current->heredocs)
		free_double_array(current->heredocs);
	free(current);
}