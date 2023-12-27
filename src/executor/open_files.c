/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:37:06 by user              #+#    #+#             */
/*   Updated: 2023/12/26 20:02:09 by user             ###   ########.fr       */
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

static int	do_greater_than(t_commands *current, int (*next_fd)[2])
{
	char	*redirect;
	int		index;
	int		file;
	int		flag;

	redirect = current->greater_than;
	if (!redirect)
		return (0);
	if (ft_strcmp(redirect, ">") && ft_strcmp(redirect, ">>"))
		return (0);
	index = 0;
	flag = get_flag(redirect);
	while (current->gt_files[index])
	{
		file = open(current->gt_files[index++], O_WRONLY | O_CREAT | flag, 0777);
		if (current->gt_files[index])
			close(file);
		else
		{
			(*next_fd)[1] = file;
			(*next_fd)[0] = file;
		}
	}
	return (file);
}

static int	do_less_than(t_commands *current)
{
	return (0);
}

void	open_files(t_commands *current, int (*next_fd)[2], int (*files)[2])
{
	(*files)[1] = do_greater_than(current, next_fd);
	(*files)[0] = do_less_than(current);
}
// O_TRUNC - para substituir ||| O_APPEND -- para concatenar
