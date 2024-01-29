/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:37 by user              #+#    #+#             */
/*   Updated: 2024/01/29 16:18:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief	Create and allocate the command data.
 * @param command the user command splitted.
 * @return the new command struct node.
 */
static t_commands	*create_new_command(char *command)
{
	char			**splitted;
	t_commands		*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	splitted = ft_split(command, '\2');
	splitted = expander(splitted);
	new->greater_than = get_greater_than(splitted);
	new->less_than = get_less_than(splitted);
	new->gt_files = get_gt_files(splitted);
	new->lt_files = get_lt_hd_files(splitted, "\7");
	new->heredocs = get_lt_hd_files(splitted, "\7\7");
	new->command = get_command(splitted);
	new->next = (void *)0;
	free_double_array(splitted);
	return (new);
}

/**
 * @brief	Add the command node to the linked list.
 * @param list the begin of the list.
 * @param command the command to stract the data.
 */
static void	add_next_command(t_commands **list, char *command)
{
	t_commands	*current;

	if (!(*(list)))
		*(list) = create_new_command(command);
	current = *(list);
	while (current->next)
		current = current->next;
	current->next = create_new_command(command);
}

void	parser(char *input)
{
	char	**splitted;
	int		i;

	i = 0;
	if (!ft_strchr(input, '\3'))
		add_next_command(&get_data()->commands, input);
	else
	{
		splitted = ft_split(input, '\3');
		while (splitted[i])
			add_next_command(&get_data()->commands, splitted[i++]);
		free_double_array(splitted);
	}
	if (i == 0)
		i = 1;
	get_data()->number_of_commands = i;
}
