#include "../../includes/minishell.h"

static t_commands	*create_new_command_value(char *command)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	if (!new)
		return ((void *)0);
	new->greater_than = NULL;
	new->gt_files = NULL;
	new->less_than = NULL;
	new->lt_files = NULL;
	new->heredocs = NULL;
	new->command = ft_split(command, ' ');
	new->next = (void *)0;
	return (new);
}

static int	add_next_node_to_commands(t_commands **list, char *command)
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
		} else if (*current->command[l-1] == '>') { // se anterior for > vai para o prox (ex: "> teste.txt" é preciso pular os dois)
			l++;
		}  else if (*current->command[l] == '<') {
			l++;
		} else if (*current->command[l-1] == '<') {
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
	int k = 0;
	int l = 0;
	int number_of_gt_files = 0;
	int number_of_lt_files = 0;
	int number_of_heredocs = 0;
	char **gt_files;
	char **lt_files;
	char **heredocs;

	while(current)
	{
		current->heredocs = NULL;
		index = 0;
		j = 0;
		k = 0;
		l = 0;
		number_of_gt_files = 0;
		while (current->command[index])
		{
			if (!ft_strcmp(current->command[index], ">") || !ft_strcmp(current->command[index], ">>"))
				number_of_gt_files++;
			if (!ft_strcmp(current->command[index], "<"))
				number_of_lt_files++;
			if (!ft_strcmp(current->command[index], "<<"))
				number_of_heredocs++;
			index++;
		}
		if (number_of_gt_files)
			gt_files = malloc(sizeof(char *) * (number_of_gt_files + 1));
		if (number_of_lt_files)
			lt_files = malloc(sizeof(char *) * (number_of_lt_files + 1));
		if (number_of_heredocs)
			heredocs = malloc(sizeof(char *) * (number_of_heredocs + 1));
		index = 0;
		while (current->command[index])
		{
			if (!ft_strcmp(current->command[index], ">") || !ft_strcmp(current->command[index], ">>"))
			{
				if (current->greater_than)
					free(current->greater_than);
				current->greater_than = ft_strdup(current->command[index]);
				index++;
				gt_files[j] = ft_strdup(current->command[index]);
				j++;
			}
			if (!ft_strcmp(current->command[index], "<"))
			{
				if (current->less_than)
					free(current->less_than);
				current->less_than = ft_strdup(current->command[index]);
				index++;
				lt_files[k] = ft_strdup(current->command[index]);
				k++;
			}
			if (!ft_strcmp(current->command[index], "<<"))
			{
				if (current->less_than)
					free(current->less_than);
				current->less_than = ft_strdup(current->command[index]);
				index++;
				heredocs[l] = ft_strdup(current->command[index]);
				l++;
			}
			index++;
		}
		if (number_of_gt_files || number_of_lt_files || number_of_heredocs)
			swap_command(&current, index);
		if (number_of_gt_files)
		{
			gt_files[j] = NULL;
			current->gt_files = gt_files;
		}
		if (number_of_lt_files)
		{
			lt_files[k] = NULL;
			current->lt_files = lt_files;
		}
		if (number_of_heredocs)
		{
			heredocs[l] = NULL;
			current->heredocs = heredocs;
		}

		if (current->next)
			current = current->next;
		else
			break;
	}
}

void	parser(char *input)
{
	char **plural;
	int i = 0;
	if (!strchr(input, '|'))
		add_next_node_to_commands(&get_data()->commands, input);
	else
	{
		plural = ft_split(input, '|');
		while(plural[i])
		{
			add_next_node_to_commands(&get_data()->commands, plural[i]);
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


	t_redirect			*greater_than;
							char	**files; = {"1", "2", "3", "teste.txt", NULL}; 
							char	**redirects = {">", ">>", ">", ">", NULL};
	t_redirect			*less_than;
							char	**files; = {"EOF", "FIM", "Makefile", NULL};
							char	**redirects = {"<<", "<<", "<", NULL};


*/