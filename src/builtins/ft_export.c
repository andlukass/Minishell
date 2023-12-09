/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:20:27 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/09 21:40:24 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*get_copy()
{
	t_env	*copy;
	t_env	*current;
	char	*variable;

	current = get_data()->env;
	copy = NULL;
	while(current)
	{
		variable = strdup(current->variable);
		add_next_node(&copy, create_new_value(variable));
		current = current->next;
	}
	return (copy);
}

static void	print_export()
{
	t_env	*current;
	t_env	*begin;
	char	*temp;
	int		compare_size;

	current = get_copy();
	begin = current;
	while(current->next)
	{
		compare_size = strchr(current->variable, '=') - current->variable;
		if(strncmp(current->variable, current->next->variable, compare_size) > 0)
		{
			temp = current->variable;
			current->variable = current->next->variable;
			current->next->variable = temp;
			current = begin;
		}
		current = current->next;
	}
	current = begin;
	while(current)
	{
		if (strchr(current->variable, '=') && !(*(strchr(current->variable, '=') + 1)))
			printf("declare -x %s''\n", current->variable);
		else
			printf("declare -x %s\n", current->variable);
		current = current->next;
	}
	free_env(begin);
}

static void	add_to_env(char *argument)
{
	t_env	*current;
	char	*variable;
	char	*old_key;
	char	*key;

	if (*argument >= '0' && *argument <= '9')
	{
		printf("'%c' identifier can't start with numbers\n", *argument);
		return;
	}
	variable = strdup(argument);
	if (strchr(variable, '='))
		key = strndup(variable, strchr(variable, '=') - variable);
	else
		key = strndup(variable, ft_strlen(variable));
	current = get_data()->env;
	while(current)
	{
		if (strchr(current->variable, '='))
			old_key = strndup(current->variable, strchr(current->variable, '=') - current->variable);
		else
			old_key = strndup(current->variable, ft_strlen(current->variable));
		if (!strcmp(old_key, key))
		{
			free(old_key);
			free(key);
			if (!strchr(variable, '='))
			{
				free(variable);
				return;
			}
			free(current->variable);
			current->variable = variable;
			return ;
		}
		free(old_key);
		current = current->next;
	}
	free(key);
	add_next_node(&get_data()->env, create_new_value(variable));
}

void	ft_export(void)
{
	t_env *current;
	int	index;

	index = 1;
	current = get_data()->env;
	if (!get_data()->input_array[1])
		print_export();
	else
		while(get_data()->input_array[index])
			add_to_env(get_data()->input_array[index++]);
}
