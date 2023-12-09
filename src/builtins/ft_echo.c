/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:58:58 by llopes-d          #+#    #+#             */
/*   Updated: 2023/12/09 23:10:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(void)
{
	int	i;

	if (strcmp(get_data()->input_array[1], "-n"))
		i = 1;
	else
		i = 2;
	while (get_data()->input_array[i])
	{
		printf("%s", get_data()->input_array[i++]);
		if (get_data()->input_array[i])
			printf(" ");
	}
	if (strcmp(get_data()->input_array[1], "-n"))
		printf("\n");
}
