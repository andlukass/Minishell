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

static int	is_duplicated(t_env	*env, char	*variable, char	*key)
{
	char	*cur_key;

	while (env)
	{
		if (strchr(env->variable, '='))
			cur_key = strndup(env->variable, \
				strchr(env->variable, '=') - env->variable);
		else
			cur_key = strndup(env->variable, ft_strlen(env->variable));
		if (!strcmp(cur_key, key))
		{
			free(cur_key);
			if (!strchr(variable, '='))
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

static void	add_to_env(char *arg)
{
	t_env	*env;
	char	*variable;
	char	*key;

	if (*arg >= '0' && *arg <= '9')
	{
		printf("'%c' identifier can't start with numbers\n", *arg);
		return ;
	}
	variable = strdup(arg);
	if (strchr(variable, '='))
		key = strndup(variable, strchr(variable, '=') - variable);
	else
		key = strndup(variable, ft_strlen(variable));
	env = get_data()->env;
	if (!is_duplicated(env, variable, key))
		add_next_node(&get_data()->env, create_new_value(variable));
	free(key);
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
