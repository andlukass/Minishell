#include "../../includes/parser.h"
#include "../../includes/minishell.h"


static t_commands	*create_new_command_value(char *command, int is_pipe)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	new->command = ft_split(command, ' ');
	new->is_pipe = is_pipe;
	new->next = (void *)0;
	return (new);
}

static int	add_next_node_to_commands(t_commands **list, char *command, int is_pipe)
{
	t_commands	*current;

	if (!(*(list)))
		return (*(list) = create_new_command_value(command, is_pipe), 0);
	current = *(list);
	while (current->next)
		current = current->next;
	current->next = create_new_command_value(command, is_pipe);
}

void	free_commands(t_commands *stack)
{
	t_commands	*current;
	t_commands	*temp;

	current = stack;
	while (current->next)
	{
		temp = current->next;
		free_double_array(current->command);
		free(current);
		current = temp;
	}
	free_double_array(current->command);
	free(current);
}

void	handle_input(void)
{
	char *input = get_data()->input;
	char **plural;
	int i = 0;
	if (!strchr(input, '|'))
		add_next_node_to_commands(&get_data()->commands, input, 0);
	else
	{
		plural = ft_split(input, '|');
		while(plural[i])
		{
			int is_pipe;
			if (plural[i+1])
				is_pipe = 1;
			else
				is_pipe = 0;
			add_next_node_to_commands(&get_data()->commands, plural[i], is_pipe);
			i++;
		}
		free_double_array(plural);
	}
	if (i == 0)
		i = 1;
	get_data()->number_of_commands = i;
}
