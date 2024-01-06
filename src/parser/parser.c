/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:09:37 by user              #+#    #+#             */
/*   Updated: 2024/01/06 11:12:17 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_commands	*create_new_command_value(char *command)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	new->greater_than = handle_redirections(command);
	new->less_than = handle_redirections(command);
	new->gt_files = NULL;
	new->lt_files = NULL;
	new->heredocs = NULL;
	new->command = get_command(command);
	new->next = (void *)0;
	return (new);
}

static int	add_next_node(t_commands **list, char *command)
{
	t_commands	*current;

	if (!(*(list)))
		return (*(list) = create_new_command_value(command), 0);
	current = *(list);
	while (current->next)
		current = current->next;
	current->next = create_new_command_value(command);
	return (0);
}

void	parser(char *input)
{
	char **plural;
	int i = 0;
	if (!strchr(input, '\3'))
		add_next_node(&get_data()->commands, input);
	else
	{
		plural = ft_split(input, '\3');
		while(plural[i])
		{
			add_next_node(&get_data()->commands, plural[i]);
			i++;
		}
		free_double_array(plural);
	}
	if (i == 0)
		i = 1;
	get_data()->number_of_commands = i;
}

/*
exemplo da struct:
echo teste > 1 >> 2 > 3 >> teste.txt mais teste kkkkkkk <<EOF <<FIM < Makefile
typedef struct s_commands{
	char				**command; = {"echo", "teste", "mais", "teste", "kkkkkkk", NULL} // array com todos os tokens do comando
	char				*greater_than; = ">>" // vai ser uma string com o ultimo greater_than usado
	char				**gt_files; = {"1", "2", "3", "teste.txt", NULL} // array com todos os nomes de arquivo para abrir
	char				*heredocs; = {"EOF", "FIM", NULL};
	char				*less_than; = "<" // vai ser uma string com o ultimo less_than usado
	char				**lt_files; = {"Makefile", NULL} // array com todos os nomes de arquivo para escutar
	struct s_commands	*next; = NULL // aponta para o proximo comando
}	t_commands;
*/