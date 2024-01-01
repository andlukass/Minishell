/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/01 12:55:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief	Capture CTRL C command and give the prompt back
 */
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_data	*data;
	char	*input;

	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	if (argc != 1)
		return (write(1, "too many arguments\n", 19));
	data = get_data();
	get_env(env);
	while (1)
	{
		get_prompt();
		input = readline(data->prompt);
		free(data->prompt);
		if (*input)
		{
			handle_input(input);
			executor(&get_data()->commands);
			free_commands(get_data()->commands);
			get_data()->commands = NULL;
			add_history(input);
		}
	}
	return (0);
}
