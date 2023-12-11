/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:20:27 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/10 14:58:03 by llopes-d         ###   ########.fr       */
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
	t_env	*current;
	char	*temp;

	current = env_copy;
	while (current->next)
	{
		if (strncmp(current->variable, current->next->variable, \
				ft_strchr(current->variable, '=') - current->variable) > 0)
		{
			temp = current->variable;
			current->variable = current->next->variable;
			current->next->variable = temp;
			current = env_copy;
		}
		current = current->next;
	}
	while (env_copy)
	{
		if (ft_strchr(env_copy->variable, '=') \
				&& !(*(ft_strchr(env_copy->variable, '=') + 1)))
			printf("declare -x %s''\n", env_copy->variable);
		else
			printf("declare -x %s\n", env_copy->variable);
		env_copy = env_copy->next;
	}
}

static int	is_duplicated(t_env	*env, char	*variable, char	*key)
{
	char	*cur_key;

	while (env)
	{
		if (ft_strchr(env->variable, '='))
			cur_key = strndup(env->variable, \
				ft_strchr(env->variable, '=') - env->variable);
		else
			cur_key = strndup(env->variable, ft_strlen(env->variable));
		if (!strcmp(cur_key, key))
		{
			free(cur_key);
			if (!ft_strchr(variable, '='))
				return (free(variable), 1);
			free(env->variable);
			env->variable = variable;
			return (1);
		}
		free(cur_key);
		env = env->next;
	}
	return (0);
}

static void	add_to_env(char *argument)
{
	t_env	*env;
	char	*variable;
	char	*key;

	variable = strdup(argument);
	key = get_env_key(argument);
	env = get_data()->env;
	if (!is_duplicated(env, variable, key))
		add_next_node(&get_data()->env, create_new_value(variable));
	free(key);
}

void	ft_export(void)
{
	t_env	*env_copy;
	int		index;
	char	*argument;

	index = 1;
	env_copy = get_copy();
	if (!get_data()->input_array[1])
		print_export(env_copy);
	else
	{
		while (get_data()->input_array[index])
		{
			argument = get_data()->input_array[index++];
			if (*argument >= '0' && *argument <= '9')
				printf("'%c' identifier can't start with numbers\n", *argument);
			else
				add_to_env(argument);
		}
	}
	free_env(env_copy);
}
