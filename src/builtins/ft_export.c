/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:20:27 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/17 22:28:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_variable(char *variable)
{
	char	*value;
	char	*key;

	key = get_env_key(variable);
	value = get_env_value(key);
	if (ft_strchr(variable, '='))
		printf("declare -x %s=\"%s\"\n", key, value);
	else
		printf("declare -x %s\n", variable);
	free(key);
}

static void	print_export(t_env *env_copy)
{
	t_env	*current;
	char	*temp;

	current = env_copy;
	while (current->next)
	{
		if (ft_strncmp(current->variable, current->next->variable, \
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
		print_variable(env_copy->variable);
		env_copy = env_copy->next;
	}
}

static int	is_valid_identifier(char *str)
{
	int	size;
	int	i;

	i = 0;
	if (ft_strchr(str, '='))
		size = ft_strchr(str, '=') - str;
	else
		size = ft_strlen(str);
	if ((str[i] > '0' && str[i] < '9') || str[i] == '=')
		return (0);
	while (str[i] && i < size)
	{
		if (!ft_isalpha(str[i]) && str[i] != '_'\
			&& !(str[i] > '0' && str[i] < '9'))
			return (0);
		i++;
	}
	return (1);
}

static void	export_add(char **command)
{
	int		index;
	char	*argument;

	index = 1;
	while (command[index])
	{
		argument = command[index++];
		if (!is_valid_identifier(argument))
		{
			get_data()->exit_status = 256;
			printf("'%s': dont have a valid identifier\n", argument);
		}
		else
		{
			argument = ft_strdup(argument);
			add_next_node(&get_data()->env, argument);
		}
	}
}

void	ft_export(char **command)
{
	t_env	*env_copy;
	t_env	*current;

	env_copy = NULL;
	current = get_data()->env;
	while (current)
	{
		add_next_node(&env_copy, ft_strdup(current->variable));
		current = current->next;
	}
	if (!command[1])
		print_export(env_copy);
	else
		export_add(command);
	free_env(env_copy);
	if (get_data()->number_of_commands > 1)
		ft_exit(NULL, 0);
	else
		return ;
}
