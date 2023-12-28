/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 09:12:56 by user              #+#    #+#             */
/*   Updated: 2023/12/28 09:13:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char **command)
{
	if (!ft_strcmp(command[0], "exit"))
		return (1);
	if (!ft_strcmp(command[0], "echo"))
		return (1);
	if (!ft_strcmp(command[0], "pwd"))
		return (1);
	if (!ft_strcmp(command[0], "unset"))
		return (1);
	if (!ft_strcmp(command[0], "export"))
		return (1);
	if (!ft_strcmp(command[0], "cd"))
		return (1);
	if (!ft_strcmp(command[0], "env"))
		return (1);
	return (0);
}
