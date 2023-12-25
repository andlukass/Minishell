/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:37:06 by user              #+#    #+#             */
/*   Updated: 2023/12/25 15:48:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_flag(char *redirect)
{
	if (!redirect)
		return (0);
	if (!ft_strcmp(redirect, ">"))
		return (O_TRUNC);
	else
		return (O_APPEND);
}

static int	is_redirect(char *redirect)
{
	if (!redirect)
		return (0);
	if (!ft_strcmp(redirect, ">"))
		return (1);
	if (!ft_strcmp(redirect, ">>"))
		return (1);
}

int	open_files(t_commands *current, int (*next_fd)[2])
{
	int	index;
	int	file;
	int	flag;

	index = 0;
	flag = get_flag(current->redirect);
	if (!is_redirect(current->redirect))
		return (0);
	while (current->files[index])
	{
		file = open(current->files[index++], O_WRONLY | O_CREAT | flag, 0777);
		if (current->files[index])
			close(file);
		else
		{
			(*next_fd)[1] = file;
			(*next_fd)[0] = file;
		}
	}
	return (file);
}
// O_TRUNC - para substituir ||| O_APPEND -- para concatenar
