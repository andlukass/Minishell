/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:20:27 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/09 22:45:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*get_copy(void)
{
	t_env	*copy;
	t_env	*current;
	char	*variable;

	current = get_data()->env;
	copy = NULL;
	while (current)
	{
		variable = strdup(current->variable);
		add_next_node(&copy, create_new_value(variable));
		current = current->next;
	}
	return (copy);
}

static void	print_export(t_env *env_copy)
{
	t_env	*cur;
	char	*temp;

	cur = env_copy;
	while (cur->next)
	{
		if (strncmp(cur->variable, cur->next->variable, \
				strchr(cur->variable, '=') - cur->variable) > 0)
		{
			temp = cur->variable;
			cur->variable = cur->next->variable;
			cur->next->variable = temp;
			cur = env_copy;
		}
		cur = cur->next;
	}
	cur = env_copy;
	while (cur)
	{
		if (strchr(cur->variable, '=') && !(*(strchr(cur->variable, '=') + 1)))
			printf("declare -x %s''\n", cur->variable);
		else
			printf("declare -x %s\n", cur->variable);
		cur = cur->next;
	}
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
	t_env	*env_copy;
	int		index;

	index = 1;
	env_copy = get_copy();
	if (!get_data()->input_array[1])
		print_export(env_copy);
	else
		while (get_data()->input_array[index])
			add_to_env(get_data()->input_array[index++]);
	free_env(env_copy);
}
