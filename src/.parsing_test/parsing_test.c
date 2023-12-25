#include "../../includes/minishell.h"

static t_commands	*create_new_command_value(char *command, int is_pipe)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	new->redirect = NULL;
	new->files = NULL;
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
	return (0);
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
		if (current->redirect) {
			free_double_array(current->files);
			free(current->redirect);
		}
		free(current);
		current = temp;
	}
	free_double_array(current->command);
	if (current->redirect) {
		free_double_array(current->files);
		free(current->redirect);
	}
	free(current);
}

void swap_command(t_commands **list, int size)
{
	t_commands	*current = *list;
	char **new_command;
	int l;
	int k;

	l = 0;
	k = 0;
	new_command = malloc(sizeof(char *) * size +1);
	while(current->command[l])
	{
		if (l == 0) { // se nao tem anterior entao é comando
			new_command[k++] = ft_strdup(current->command[l++]);
		} else if (*current->command[l] == '>') { // se atual for > vai para o proximo
			l++;
		} else if (*current->command[l-1] == '>') {
			l++;
		} else {
			new_command[k++] = ft_strdup(current->command[l++]);
		}
	}
	new_command[k] = NULL;
	free_double_array(current->command);
	current->command = new_command;
}

void	handle_redirects(t_commands **list)
{
	t_commands	*current = *list;
	int index = 0;
	int j = 0;
	int number_of_files = 0;
	char **files;

	while(current)
	{
		index = 0;
		j = 0;
		number_of_files = 0;
		while (current->command[index])
		{
			if (!ft_strcmp(current->command[index], ">") || !ft_strcmp(current->command[index], ">>"))
				number_of_files++;
			index++;
		}
		if (number_of_files)
			files = malloc(sizeof(char *) * (number_of_files + 1));
		index = 0;
		while (current->command[index])
		{
			if (!ft_strcmp(current->command[index], ">") || !ft_strcmp(current->command[index], ">>"))
			{
				current->redirect = ft_strdup(current->command[index]);
				index++;
				files[j] = ft_strdup(current->command[index]);
				j++;
			}
			index++;
		}
		if (number_of_files)
			swap_command(&current, index);
		if (number_of_files)
			files[j] = NULL;
		current->files = files;

		if (current->next)
			current = current->next;
		else
			break;
	}
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
	handle_redirects(&get_data()->commands);
	if (i == 0)
		i = 1;
	get_data()->number_of_commands = i;
}

/*
exemplo:
echo teste > 1 > 2 > 3 > teste.txt mais teste kkkkkkk
typedef struct s_commands{
	char				**command; = {"echo", "teste", "mais", "teste", "kkkkkkk"} // array com todos os tokens do comando
	int					is_pipe; = 0 // se tem pipe no final do comando
	char				**files; = {"1", "2", "3", "teste.txt"} // array com todos os nomes de arquivo
	char				*redirect; = ">" // vai ser uma string com sempre o ultimo redirect usado
	struct s_commands	*next; = NULL // aponta para o proximo comando
}	t_commands;
*/