/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:56:31 by user              #+#    #+#             */
/*   Updated: 2024/02/01 17:06:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *value, char *message)
{
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, message, ft_strlen(message));
}

void	redirect_error(char *file)
{
	if (!ft_strcmp(file, "./\2/\2"))
		print_error("", "ambiguos redirect\n");
	else
		print_error(file, ": No such file or directory\n");
}
