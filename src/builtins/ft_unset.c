/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:19:38 by user              #+#    #+#             */
/*   Updated: 2023/12/11 00:00:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(void)
{
	int	i;

	i = 1;
	while (get_data()->input_array[i])
		remove_env_value(get_data()->input_array[i++]);
}
