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

void	parser(char *input)
{
	char **plural;
	int i = 0;
	if (!strchr(input, '\3'))
		add_next_node_to_commands(&get_data()->commands, input);
	else
	{
		plural = ft_split(input, '\3');
		while(plural[i])
		{
			add_next_node_to_commands(&get_data()->commands, plural[i]);
			i++;
		}
		free_double_array(plural);
	}
	// handle_redirects(&get_data()->commands);
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






1 identificar os nomes dos arquivos das redireçoes e salvar em (gtf)
2 identificar os nomes dos arquivos das redireçoes e salvar em (ltf)







*/