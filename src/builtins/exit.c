/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:24:50 by llopes-d          #+#    #+#             */
/*   Updated: 2023/11/28 20:51:14 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_exit(void)
{
	printf("exit\n");
	free(get_data()->username);
	free_env(get_data()->env);
	rl_clear_history();
	exit(0);
}
