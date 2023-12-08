/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:20:27 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/08 16:16:02 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//sem args: deve mostrar todo o env 
//com 1 arg: se receber uma string sem '=' adiciona ao env
//com 2+ args: so aceita o segundo arg se o arg for o nome de alguma var ja existente ou o nome da que esta a ser criada

static void	print_export()
{
	
}

void	ft_export(void)
{
	t_env *current;

	current = get_data()->env;
	if (!get_data()->input_array[1])
	while(current)
	{
		if(current->key)
			printf("%s=%s\n",current->key, current->value);
		current = current->next;
	}
}
