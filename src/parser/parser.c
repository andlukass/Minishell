/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbraz-d <isbraz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:37 by user              #+#    #+#             */
/*   Updated: 2024/01/07 14:40:47 by isbraz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_commands	*create_new_command(char *command)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	new->greater_than = get_last_redirection(command, '>');
	new->less_than = get_last_redirection(command, '<');
	new->gt_files = NULL;
	new->lt_files = NULL;
	new->heredocs = NULL;
	new->command = get_command(command);
	new->next = (void *)0;
	return (new);
}

static int	add_next_command(t_commands **list, char *command)
{
	t_commands	*current;

	if (!(*(list)))
	{
		*(list) = create_new_command(command);
		return (0);
	}
	current = *(list);
	while (current->next)
		current = current->next;
	current->next = create_new_command(command);
	return (0);
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
