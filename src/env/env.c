/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:21:22 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/09 17:30:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *stack)
{
	t_env	*current;
	t_env	*temp;

	current = stack;
	while (current->next)
	{
		temp = current->next;
		free(current->variable);
		free(current);
		current = temp;
	}
	free(current->variable);
	free(current);
}

t_env	*create_new_value(char *variable)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->variable = variable;
	new->next = NULL;
	return (new);
}

void	add_next_node(t_env **list, t_env *new)
{
	t_env	*current;
	char	*old_key;
	char	*key;

	if (strrchr(new->variable, '='))
		key = strndup(new->variable, strrchr(new->variable, '=') - new->variable);
	else
		key = strndup(new->variable, ft_strlen(new->variable));

	if (*(list))
	{
		current = *(list);
		while (current->next)
		{
			if (strrchr(current->variable, '='))
				old_key = strndup(current->variable, strrchr(current->variable, '=') - current->variable);
			else
				old_key = strndup(current->variable, ft_strlen(current->variable));
			if (!strcmp(old_key, key))
			{
				current->variable = new->variable;
				free(new->variable);
				free(new);
				free(old_key);
				free(key);
				return;
			}
			free(old_key);
			current = current->next;
		}
		current->next = new;
	}
	else
		*(list) = new;
	free(key);
}

char	*get_env_value(char *key)
{
	t_env	*current;
	char	*old_key;


	current = get_data()->env;
	if (get_data()->env)
	{
		while (current->next)
		{
			if (strrchr(current->variable, '='))
				old_key = strndup(current->variable, strrchr(current->variable, '=') - current->variable);
			else
				old_key = strndup(current->variable, ft_strlen(current->variable));
			if (!strcmp(old_key, key))
			{
				free(old_key);
				return (strrchr(current->variable, '=') + 1);
			}
			free(old_key);
			current = current->next;
		}
		return (NULL);
	}
	else
		return (NULL);
}

void	get_env(char *env[])
{
	int		index;
	char	*variable;
	char	*level;

	index = 0;
	while (env[index])
	{
		if (!strncmp(env[index], "SHLVL", 5))
		{
			level = ft_itoa(atoi(&env[index][6]) + 1);
			variable = ft_strjoin("SHLVL=", level, NO_FREE);
			free(level);
		}
		else
			variable = strndup(env[index], ft_strlen(env[index]));
		add_next_node(&get_data()->env, create_new_value(variable));
		index++;
	}
}
