/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:43:23 by user              #+#    #+#             */
/*   Updated: 2024/01/25 15:53:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_executor(t_exec *exec, int exit_status)
{
	free(exec->pids);
	get_data()->quit = 0;
	close_fds(exec->fd);
	close_fds(exec->files);
	close_fds(exec->next_fd);
	if (exit_status != -1)
		ft_exit(NULL, exit_status);
	return ;
}
