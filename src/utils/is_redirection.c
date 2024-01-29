/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:42:48 by user              #+#    #+#             */
/*   Updated: 2024/01/29 15:43:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, "\6") || \
		!ft_strcmp(str, "\6\6") || \
		!ft_strcmp(str, "\7") || \
		!ft_strcmp(str, "\7\7"))
		return (1);
	return (0);
}
