/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/01 21:01:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

/**
 * @brief	Capture CTRL C command and give the prompt back
 */
void	signal_handler(int sig)
{
	if (sig == SIGINT && get_data()->interactive)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	*prompt;

	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	if (argc != 1)
		return (write(1, "too many arguments\n", 19));
	get_env(env);
	get_data()->exit_status = 0;
	while (1)
	{
		get_data()->interactive = 1;
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		get_data()->interactive = 0;
		if (!input)
			ft_exit(NULL);
		if (*input)
			handle_input(input);
	}
	return (0);
}
