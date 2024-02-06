/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopes-d <llopes-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:17:48 by user              #+#    #+#             */
/*   Updated: 2024/02/06 18:12:32 by llopes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
		get_data()->ctrl = 1;
	if (sig == SIGQUIT)
		get_data()->sig_quit = 1;
}

void	signal_handler_main(int sig)
{
	if (sig == SIGINT && get_data()->interactive)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_data()->exit_status = 256 * 130;
	}
}

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		printf("\n");
		get_data()->quit = 1;
	}
}
