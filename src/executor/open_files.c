/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 12:37:06 by user              #+#    #+#             */
/*   Updated: 2023/12/27 18:13:28 by user             ###   ########.fr       */
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
			(*next_fd)[0] = 0;
		}
	}
	return (file);
}

static int	do_less_than(t_commands *current)
{
	int	index;
	int	file;

	index = 0;
	file = 0;
	// return 0;
	if (current->less_than && !ft_strcmp(current->less_than, "<") && \
		(ft_strcmp(current->command[0], "exit") && ft_strcmp(current->command[0], "export") && \
		ft_strcmp(current->command[0], "unset") && ft_strcmp(current->command[0], "cd")))
	{
		while(current->lt_files[index])
		{
			if (!current->lt_files[index + 1])
				file = open(current->lt_files[index], O_RDONLY, 0777);
			index++;
		}
	}
	return (file);
}

void	open_files(t_commands *current, int (*next_fd)[2], int (*files)[2])
{
	(*files)[1] = do_greater_than(current, next_fd);
	(*files)[0] = do_less_than(current);
}
// O_TRUNC - para substituir ||| O_APPEND -- para concatenar
